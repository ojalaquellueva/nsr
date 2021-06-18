# Native Status Resolver (NSR)

Author: Brad Boyle (bboyle@email.arizona.edu)  


## Table of Contents

- [Overview](#overview)
- [BIEN NSR](#bien-nsr)
- [Database](#database)
- [Interfaces](#interfaces)
- [Top-level scripts](#scripts)
- [Example scripts](#example-scripts)
- [Software requirements](#software)
- [Installation](#installation)
  - [Database and batch application](#install-core)
  - [API](#install-api)
- [Usage](#usage)
  - [Build NSR database](#db)
  - [Command Line (NSR Batch)](#batch)
     - [Input](#input)
     - [Output](#output)
  - [NSR API](#api)
     - [Input](#api-input)
     - [Output](#api-output)
     - [API examples](#api-examples)
- [Native Status Codes](#status-codes)


<a name="overview"></a>
## Overview

The Native Status Resolver (NSR) is a data validation service which determines if a species (or other taxon such as genus or family) is native or introduced within the political division of observation. The NSR make this determination by comparison against country-, state- or county-level checklists.

The NSR accepts as input one or more observations of a taxon in a political division (country, plus optionally state/province or county/parish). For each observation, the NSR returns an opinion as to whether that taxon is native or introduced in the lowest political division submitted. Native status opinions are determined by consulting one or more species checklists for the region in question. If no checklist is available for the region submitted, the NSR returns no opinion. In some cases, even if no checklist is available for the political division of observation, the NSR may  be able to assign a status of "introduced" if the taxon is endemic to a different, non-overlapping political division.

If the taxon submitted is not present in any checklist for the region of observation, the NSR will also search higher taxa for opinions indicating the taxon is introduced in the region of observation.  If a species is introduced then all varieties and subspecies must also be introduced. Conversely, an opinion of "native" for a lower taxon is also applied to the higher taxa to which it belongs. If a variety is native to a particular region, that automatically means that the species, genus and family to which that variety belongs are also native. In other words, "native" propagates up the taxonomic hierarchy, and "introduced" propagates down the taxonomic hierarchy.

For example, if Poa annua var. supina is submitted, but no opinion is available for the variety, the NSR will check for opinions for Poa annua and Poa. If an opinion is discovered indicating that Poa annua is introduced to the region of observation, then the NSR will report that Poa annua var. supina is introduced.

The NSR uses a similar hierarchical approach for political divisions, transferring "native" up the political division hierarchy and "introduced" down the hierarchy. For example, a species recorded as "native" in a county-level checklist will also be flagged as native to the containing state and country. Similarly, a species that is "introduced" according to a country will also be flagged as introduced to a state in that country, even if no checklist is available for that state.

This repository contains source code for the NSR core application and API. For code used to build the NSR database, see separate repository `See separate repository https://github.com/ojalaquellueva/nsr_db`.

<a name="bien-nsr"></a>
## BIEN NSR

The [BIEN NSR](https://bien.nceas.ucsb.edu/bien/tools/nsr/) provides access to an NSR database populated with multiple checklists providing nearly complete global coverage. The majority of the checklists in the BIEN NSR are high-quality published species lists prepared by professional taxonomists as part of floras or other floristic projects. For details of BIEN NSR sources, see respository `https://github.com/ojalaquellueva/nsr_db` for details. The BIEN NSR can be accessed via all of the interfaces listed below (see [Interfaces](#interfaces)). 

<a name="database"></a>
## NSR Database

The NSR database is a MySQL database populated with one or more taxonomic country-, state- or county-level checklists, plus supporting lookup tables of political divisions and taxa. Political division name are standardized according to Geonames (geonames.org) using the GNRS (see `https://github.com/ojalaquellueva/gnrs`). Assembly of the NSR database is performed by a separate pipeline of PHP and SQL scripts. See respository `https://github.com/ojalaquellueva/nsr_db` for details.

<a name="interfaces"></a>
## Interfaces

The NSR can be accessed via the following interfaces:

* [NSR Batch Application](#batch). The NSR can be accessed locall via the command line by calling `nsr_batch.php`. 
* [NSR API](#api). The NSR Batch API supports requests of up to 5000 taxon + political division combinations per call. Request must be sent as JSON-encoded POST data. Results are returned as JSON.
* [RNSR R Package](https://github.com/EnquistLab/RNSR). The RNSR R package provides a simplified interface to the [NSR Batch API](#batch) via a family of R language functions. As with the parent API, it support up to 5000 taxon + political division combinations per call. RNSR can be downloaded from repository https://github.com/EnquistLab/RNSR.

<a name="scripts"></a>
## Top-level scripts

#### `nsr.php`   
- Core application, evaluates table of observations against reference tables and populates native status opinion columns.  
- Called by `nsr_batch.php` and `nsr_ws.php` 

#### `nsr_batch.php`    
- NSR batch processing application  
- Calls `nsr.php`  
- Processes multiple observations at once  
- Uploads observations as CSV file from data directory 
- Exports NSR results as TAB delimited file to data directory  
- Requires shell access to this server  
- Called by `nsr_wsb.php`

#### `nsr_wsb.php`   
- NSR API
- Processes up to 5000 observations per call  
- Calls `nsr_batch.php`

<a name="example-scripts"></a>
## Example Scripts

#### `nsr_api_example.php`   
- Example of calling the NSR API using PHP

#### `nsr_api_example.R`   
- Example of calling the NSR API using R

<a name="software"></a>
## Software requirements
* OS: Runs on a unix/linux. The [BIEN NSR](#bien-nsr) is currently running on Ubuntu 18.04.5.
* PHP 7.0 or greater
* MySQL 5.5 or greater
* Fully populated NSR MySQL database, with read-only nsr user (see separate repository `https://github.com/ojalaquellueva/nsr_db` for details).

<a name="installation"></a>
## Installation & setup

The following steps assume two installations: one in public_html for the web service, and a second installation elsewhere in the file system for creating the database and running the batch applications. Other configurations may be used as well.

<a name="install-core"></a>
### Database and batch application
1. Clone this repository to location of choice, using recursive option to include submodules:

```
git clone --recursive https://github.com/ojalaquellueva/nsr.git
```

2. Set up MySQL database
   * Create empty NSR database.
   * Create admin-level and select-only NSR database users, using user names and passwords of your choice.
3. Copy read-only database config file (db_config-example.php) as db_config.php to location outside the application directory and set the parameters.
4. Copy write-access database config file (db_configw-example.php) as db_configw.php to location outside the application directory and set the parameters.
5. Copy or rename example parameters file (params.example.php) to params.php to same location (inside the main application directory) and set the parameters.
6. Prepare NSR database checklist data sources and set database parameters as described in nsr_db/README.md
7. Build NSR database
8. The following file is used only by the web service and can be removed if not needed:

```
rm nsr_ws.php
rm nsr_wsb.php
```

<a name="install-api"></a>
### API

The following instructions assume:
* NSR database is installed and configured as described above
* Valid virtual host and port have been configured for the API root directory

1. Clone this repository to API root directory of your choice (e.g., `/var/www/public_html/nsr/`), using recursive option to include submodules:

```
git clone --recursive https://github.com/ojalaquellueva/nsr.git
```

2. Copy read-only database config file (`db_config-example.php`) as `db_config.php` to location outside `public_html` and set the parameters.
3. Copy write-access database config file (`db_configw-example.php`) as `db_configw.php` to location outside `public_html` and set the parameters.
4. Copy or rename parameters file (`params.example.php`) to `params.php` and set the parameters.
5. Adjust file system permissions as per your server settings.
6. The following files, directories and their contents are not used by web service and should be removed:

```
rm -rf nsr_batch_includes/
rm -rf nsr_db/
rm db_batch_connect.php
rm nsr_batch.php
```

<a name="usage">
## </a>Usage

### <a name="db"></a>Build NSR database

See separate repository `https://github.com/ojalaquellueva/nsr_db`.

<a name="batch"></a>
### Command Line (NSR Batch)

Syntax:  

```
php nsr_batch.php -e=<echo> -i=<interactive_mode_on> -f=<inputfile> -l=<line_endings> -t=<inputfile_type> -r=<replace_cache>
```

#### Options  
* Default values in **bold** 

| Option	| Meaning | Values
| --------- | ------------------- | --------------------
| -e | terminal echo on | __true__,false
| -i | interactive mode | true,__false__ 
| -f | input file name |  
| -l | line-endings | unix,__mac__,win
| -t | inputfile type | __csv__,tab
| -r | replace the cache | true,__false__  

Example:  

```
php nsr_batch.php -i=true -f='my_observations.txt' -l=unix -t=tab

```

Notes:  
* Use -r=false to retain all previously cached results. Option -r=true is used only when NSR reference database has changed and previous results may not be valid.  
* When the NSR has finished running, results file will be saved to the NSR data directeory
* Results file has same base name as input file, plus suffix "_nsr_results.txt" 
* Results file is tab-delimitted, regardless of the format of the input file.  

<a name="input"></a>
#### Input

The NSR accepts as input a plain text file containing a header plus one or more observations of taxon in political division, formatted as follows (optional values in square brackets; if county_parish is included, state_province must be included as well):  

```
taxon,country,state_province,county_parish,user_id
taxon,country[,state_province[,county_parish]][, user_id]]  
taxon,country[,state_province[,county_parish]][, user_id]]  
taxon,country[,state_province[,county_parish]][, user_id]]  
```

The first line must be the header. Actual column names are ignored as this line is discarded. However, if you leave out the header, the first line of data will be ignored. 

Taxon names can be of any of the following ranks: family, genus, species, subspecies, variety, forma. Do not include authors.

Spellings of political division names in the NSR database are the plain ascii (unaccented) versions of English-language political division names in Geonames (`www.geonames.org`). Political division names in user input should therefore be standardized according to the same standard. Although state_province and county_parish are both optional, if county is included its containing state_province must also be present. 

Optional user_id can be used to include a single-column unique identifier for each line. Such identifiers simplify joining NSR results back to the user's original dataset.

Although optional columns can be left blank, column numbers are fixed. For example, user_id is always the fifth column. Although the fields populated can vary among rows, the input file must have the same number of columns per line. The following examples should clarify these requirements.

##### Example input files

Below is an example of a valid input file, suitable for processing with NSR Batch:

```
taxon,country,state_province,county_parish
Pinus ponderosa,United States,Arizona,Pima
Eucalyptus,Australia,Western Australia,
Abrothallus bertianus,Austria,,
Cocos nucifera,Jamaica,,
Eucalyptus,Mexico,,
Larrea tridentata,Mexico,,
```

The same example as above, with user_id included:

```
taxon,country,state_province,county_parish,user_id
Pinus ponderosa,United States,Arizona,Pima,1
Eucalyptus,Australia,Western Australia,,2
Abrothallus bertianus,Austria,,,3
Cocos nucifera,Jamaica,,,4
Eucalyptus,Mexico,,,5
Larrea tridentata,Mexico,,,6
```

Another example of a valid input file, containing taxon names and countries only:

```
taxon,country
Pinus ponderosa,United States
Eucalyptus,Australia
Abrothallus bertianus,Austria
Cocos nucifera,Jamaica
Eucalyptus,Mexico
Larrea tridentata,Mexico
```

<a name="output"></a>
#### Output

The NSR batch application returns original rows and values as submitted, plus columns indicating whether taxon is native in each level of observation within the political division hierarchy, an overall assessment of native status within the lowest political division of observation, a short explanation of how the decision was reached, and a list of checklist sources consulted.   

| Column	| Meaning (values)
| --------- | -------------------
| native\_status\_country	| Native status in country (see native status values, below)
| native\_status\_state\_province	| Native status in state\_province, if any (see native status values, below)
| native\_status\_county\_parish	| Native status in county\_parish, if any (see native status values, below)
| native\_status	| Overall native status in lowest declared political division (see [Native Status Codes](#status-codes))
| native\_status\_reason	| Reason native status was assigned
| native\_status\_sources	| Checklists used to determine native status
| isIntroduced	| Simplified overall native status (1=introduced;  0=native; blank=status unknown)
| isCultivatedNSR	| Species is known to be cultivated in declared region  (1=cultivated;  0=wild or status unknown)

<a name="api"></a>
### NSR API

The NSR API offers four modes (api routes): "resolve", "meta", "sources", "citations". As with the command line core service, `nsr_batch.php`, the API resolve mode resolves native status for batches of taxon observations. The remaining three modes return metadata about NSR checklist sources and the NSR itself. Mode "meta" returns version information for NSR source code and database. Mode "sources" returns information on all checklist sources (except for literature citations). Mode "citations" returns bibtex-formatted literature citations (if available) for NSR checklist sources. 

In resolve mode, the NSR API accepts & processes up to 5000 observations in a single call. Request data must be JSON-encoded and sent as a POST request, with HTTP header set to "Content-Type: application/json". Results are returned as JSON. See [Input](#batch-api-input) for a description of input file format. Use of the API is best understood by examining the PHP and R example files (see [Batch API Examples](#batch-api-examples).

<a name="api-input"></a>
#### Input

Raw input for the API are similar to those of the NSR Batch Application (see above). The only difference is that you must include placeholders for all five columns, even if optional columns are left blank.

```
taxon,country,[state_province],[county_parish],[user_id]]  
```

An example input file is shown below. The first line must be the header. If you leave out the header, the first line of data will be ignored. 

```
taxon,country,state_province,county_parish,user_id
Pinus ponderosa,United States,Arizona,Pima,1
Eucalyptus,Australia,Western Australia,,2
Abrothallus bertianus,Austria,,,3
Cocos nucifera,Jamaica,,,4
Eucalyptus,Mexico,,,5
Larrea tridentata,Mexico,,,6
```

<a name="api-output"></a>
#### Output

NSR API output is similar to the [NSR Batch command line application output](#output), with the addition of the (optional) column `user_id` (see [API Input Format](#api-input)). See also [Native Status Codes](#status-codes).

<a name="api-examples"></a>
#### API Examples

The following scripts provide examples of calling the NSR API using PHP and R:

* ***`nsr_api_example.php`***
   * To run this example, you will need input file `nsr_testfile.csv` in directory `data/user/`.
* ***`nsr_api_example.R`***
   * To run this example, you will need input file `nsr_testfile.csv` in directory `data/user/`. Place the example file in the same directory as the R file, or modify the input file path in the R script.

Both scripts load the following example file as input data:

* ***`data/user/nsr_testfile.csv`***

<a name="status-codes"></a>
## Native Status Codes

For each observation (taxon + political division combination)submitted, the NSR returns one of the following native status codes: 

| Native status code	| Meaning 
| --------- | -------------------
| P	| Present in checklist for region of observation but no explicit status assigned
| N	| Native to region of observation
| Ne | Native and endemic to region of observation
| A	 | Absent from all checklists for region of observation
| I	| Introduced, as declared in checklist for region of observation
| Ie | Endemic to other region and therefore introduced in region of observation
| UNK | Unknown; no checklists available for region of observation and taxon not endemic elsewhere

