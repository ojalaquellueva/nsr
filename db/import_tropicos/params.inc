<?php

//////////////////////////////////////////////////
// Distributions source parameters
//////////////////////////////////////////////////

// Name which uniquely identifies this source within database
// Many operations, including table names, depend on this parameter
// REQUIRED
// MUST BE UNIQUE
// NO SPACES
// MAX 50 characters
$source_name="tropicos";

// Comprehensiveness of this source. Two options:
// 1
//		=comprehensive. Includes all species from focal region in focal taxon. Absence from 
//		list may indicates non-native species
// 0
//		=selective, not comprehensive. Not all taxa in region(s) include, absence not interpretable
$is_comprehensive=1;

// Regional scope (political division level) of this source. For comprehensive sources, 
// lower political divisions will also be treated as comprehensive, but but higher 
// political divisions will not. For example, for a comprehensive checklist at the 
// county level, species not on the list can be treated as non-native at the county 
// level. However, at the state and country level, only presences can be interpreted. 
// Three options:
//		country
//		state_province
// 		county_parish
// 
$regional_scope="country";

// List of countries for which this source provides comprehensive
// checklists. Spellings MUST agree with spellings in table country.
// Leave empty if none. Enter names in single quotes separated by
// commas: "'countryA','countryB','countryC'" 
$cclist_countries="
'Ecuador',
'Peru',
'Bolivia'
";

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
$source_name_full="Missouri Botanical Gardens country checklists";

// Primary url for this source (optional)
$source_url="www.http://services.tropicos.org/";	

// bibtext formatted citation for thsi source
$citation="";

// Person who provided access to source (optional)
$source_contact_name="Peter Jorgensen";
$source_contact_email="";

// Date accessed
// yyyy-mm-dd format
$date_accessed="2014-03-10";

// Short list of regions covered by this source, to 250 characters
$focal_regions="Bolivia, Ecuador, Peru";


// Replace previous records for this source?
// VERY IMPORTANT
// Set=true to replace all previous records for this source.
// Set=false to keep existing records (name+author) and add new records only.
$replace=true;


//////////////////////////////////////////////////
// Raw data file parameters
//////////////////////////////////////////////////

// Directory in which data for this source are stored
$datapath = $data_dir . $source_name."/";		

// list of prefixes of individual raw data tables
// these MUST be same as prefix of raw data files, minus the extension
$tbl_list = array(
	"bolivia",
	"ecuador",
	"peru"
);

// extension of raw data files. Must be the same for all
$file_ext = ".txt";

// names of destination mysql table
$tbl_names_raw=$source_name."_raw";

//////////////////////////////////////////////////
// LOAD DATA INFILE parameters
//////////////////////////////////////////////////

// Import parameters for text file
// Needed for 'LOAD DATA INFILE' statement
// Set any variable to empty string to remove entirely
$local = " LOCAL ";	// LOCAL keyword
//$fields_terminated_by = " FIELDS TERMINATED BY ',' ";
$fields_terminated_by = " FIELDS TERMINATED BY '\t' ";
$optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  // use if text surrounded by quotes
//$optionally_enclosed_by = "";
$lines_terminated_by = " LINES TERMINATED BY '\r\n' ";
$ignore_lines = " IGNORE 1 LINES ";	// Ignore header line?

// In most cases the following should be blank, but you may need to import
// as the original character set if you are getting error "Invalid utf8mb4 
// character string". This will not affect the final table character set,
// which should remain utf8mb4.
$character_set = "";
$character_set = " CHARACTER SET latin1 ";

//////////////////////////////////////////////////
// Cleanup parameters
//////////////////////////////////////////////////

// Comma-delimited list of temporary tables 
// associated with this source, with each table
// name in single quotes, no comma after last element
// For use in SQL IN list when deleting or moving tables
$temp_tbl_list="
'tropicos_raw'
";

?>
