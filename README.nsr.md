# BIEN Native Status Resolver (NSR)

## Table of Contents

- [Overview](#Overview)
- [Usage](#Usage)
- [Output schema](#Schema)
- [Native Status Codes](#Native)

## <a name="Overview"></a>Overview

Determines if a taxon is native or introduced within the political division of observation. Accepts one or more observations of taxon in political division, formatted as follow (optional values in brackets):  

taxon,country[,state_province[,county_parish]  
taxon,country[,state_province[,county_parish]  
taxon,country[,state_province[,county_parish]  

Returns original rows, plus columns indicating whether taxon is native in each level of observation within the political division hierarchy, an overall assessment of native status within the lowest political division of observation, a short explanation of how the decision was reached, and a list of checklist sources consulted.   

Observations are evaluated with respect to regional checklists in the NSR database. If not checklist is available for the region submitted, the NSR returns no opinion.   

The NSR consists uses php and mysql, and consists of three applications run by the following "master scripts", which call all others:

1. nsr.php  
- Core application, evaluates table of observations against reference tables and populates native status opinion columns.  

3. nsr_batch.php  
- NSR batch processing application  
- Processes multiple observations at once  
- Uploads observations as CSV file from data directory 
- Exports NSR results as TAB delimited file to data directory  
- Requires shell access to this server  

2. nsr_ws.php  
- NSR web service
- Processes one observation at a time via URL request

## <a name="Usage"></a>Usage

General:

```
php nsr_batch.php -e=<echo> -i=<interactive_mode_on> -f=<inputfile> -l=<line_endings> -t=<inputfile_type> -r=<replace_cache>

```

Options (default in __bold__):  
-e: terminal echo on [__true__,false]  
-i: interactive mode [true,__false__]  
-f: input file name ['__nsr_input.csv__']  
-l: line-endings [unix,__mac__,win]  
-t: inputfile type [__csv__,tab]  
-r: replace the cache [true,__false__]  

Example:  

```
php nsr_batch.php -i=true -f='my_observations.txt' -l=unix -t=tab

```

Notes:  
* Use -r=false to retain all previously cached results. Option -r=true is used only when NSR reference database has changed and previous results may not be valid.  
* When the NSR has finished running, results file will be saved to the NSR data directeory
* Results file has same base name as input file, plus suffix "_nsr_results.txt" 
* Results file is tab-delimitted, regardless of the format of the input file

## <a name="Schema">Output schema

| Column	| Meaning (values)
| --------- | -------------------
| native_status_country	| Native status in country (see native status values, below)
| native_status_state_province	| Native status in state_province, if any (see native status values, below)
| native_status_county_parish	| Native status in county_parish, if any (see native status values, below)
| native_status	| Overall native status in lowest declared political division (see native status values, below)
| native_status_reason	| Reason native status was assigned
| native_status_sources	| Checklists used to determine native status
| isIntroduced	| Simplified overall native status (1=introduced;  0=native; blank=status unknown)
| isCultivatedNSR	| Species is known to be cultivated in declared region  (1=cultivated;  0=wild or status unknown)

## <a name="Native">Native Status Codes

| Native status code	| Meaning 
| --------- | -------------------
| P	| Present in checklist for region of observation but no explicit status assigned
| N	| Native to region of observation
| Ne | Native and endemic to region of observation
| A	 | Absent from all checklists for region of observation
| I	| Introduced, as declared in checklist for region of observation
| Ie | Endemic to other region and therefore introduced in region of observation
| UNK | Unknown; no checklists available for region of observation and taxon not endemic elsewhere
