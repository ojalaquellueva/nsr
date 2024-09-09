<?php

//////////////////////////////////////////////////
// Distributions source parameters
//////////////////////////////////////////////////

// Note: $cclist_countries and $cclist_states not declared 
// as parameters for this source. Both are set dynamically by 
// querying the raw data. See scripts prepare_cclist_countries.inc
// and prepare_cclist_states.inc for details.

// Name which uniquely identifies this source within database
// Many operations, including table names, depend on this parameter
// REQUIRED
// MUST BE UNIQUE
// MUST BE SAME AS NAME OF THIS DIRECTORY, MINUS PREFIX "import_"
// MUST BE SAME AS NAME OF DATA DIRECTORY FOR THIS SOURCE
// PLAIN ASCII LETTERS AND UNDERSCORES ONLY, NO SPACES
// MAX 50 CHARACTERS
$source_name="powo";

// Comprehensiveness of this source. Two options:
// 1: comprehensive. Includes all species from focal region in focal taxon. 
// 	Absence from list may indicates non-native species
// 0: partial, not comprehensive. Not all taxa in region(s) included. 
// 	Absence not used to infer native_status.
$is_comprehensive=1;

// Regional scope (political division level) of this source. 
// For comprehensive sources, lower political divisions will also be treated
// as comprehensive, but higher political divisions will not. For example, 
// for a comprehensive checklist at the county level, species not on the list
// can be treated as non-native at the county level. However, at the state 
// and country level, only presences can be interpreted. 
//
// Note: Generally not used for this source. Comprehensive checklist 
// political divisions are set by lists of countries and states 
// extracted directly from raw data. But KEEP to avoid breaking anything.
// Three options:
//		country
//		state_province
// 		county_parish
// 
$regional_scope="country";

// Taxonomic scope
//	Highest taxonomic group encompassed by this source. Can be left blank.
//	In general, this should be "tracheophytes", "embryophytes", "bryophytes",
// 	but can also be a family if this is a monographic. Currently not used;
//	Would need to detect major higher taxon to use this information.
$taxonomic_scope="tracheophytes";
//$taxonomic_scope="";

// Longer, more descriptive name for source
// Can have spaces; not used in any scripts
// after adding to table `source`
$source_name_full="Plants of the World Online";

// Primary url for this source (optional)
$source_url="http://www.plantsoftheworldonline.org/";	

// bibtext formatted citation for thsi source
$citation="";

// Person who provided access to source (optional)
$source_contact_name="";
$source_contact_email="";

// Date accessed
// yyyy-mm-dd format
$date_accessed="2020-08-01";

// Short list of regions covered by this source, to 250 characters
$focal_regions="Global";

// Note: $cclist_countries NOT set as parameter. Will be extracted on the fly
// from data. Do NOT set here.

// Replace previous records for this source?
// VERY IMPORTANT
// Set=true to replace all previous records for this source.
// Set=false to keep existing records (name+author) and add new records only.
$replace=true;

// True to drop raw data and intermediate tables, false to drop
$drop_raw=false;

//////////////////////////////////////////////////
// Raw data file parameters
// See README in data directory for details
//////////////////////////////////////////////////
// Name of main file you will be importing
$file_raw = "POW_combined.20200731.final.txt";
//$file_raw = "POWO_sample.txt";	// For testing

// TDWG region codes
$file_raw_codes = "TDWG_region_codes_edited.csv";

// names of destination mysql table
$tbl_raw=$src."_raw";

// Directory in which data for this source are stored
$datapath = $data_dir . $source_name."/";		
$datapath = $data_dir . $source_name."/"."BIEN4.2/";	// for testing with old data

//////////////////////////////////////////////////
// LOAD DATA INFILE parameters
//////////////////////////////////////////////////

// Import parameters for main text file
// Needed for 'LOAD DATA INFILE' statement
// Set any variable to empty string to remove entirely
$local = " LOCAL ";	// LOCAL keyword
//$fields_terminated_by = " FIELDS TERMINATED BY ',' ";
$fields_terminated_by = " FIELDS TERMINATED BY '\t' ";
$optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  // use if text surrounded by quotes
//$optionally_enclosed_by = "";
$lines_terminated_by = " LINES TERMINATED BY '\n' ";
$ignore_lines = " IGNORE 1 LINES ";	// Ignore header line?

//////////////////////////////////////////////////
// Cleanup parameters
//////////////////////////////////////////////////

// Comma-delimited list of temporary tables 
// associated with this source, with each table
// name in single quotes, no comma after last element
// For use in SQL IN list when deleting or moving tables
$temp_tbl_list="
'powo_cclist_states',
'powo_poldivs',
'powo_poldivs_gnrs',
'powo_region_codes'
";


?>
