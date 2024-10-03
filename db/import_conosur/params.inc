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
$source_name="conosur";

// Longer, more descriptive name for source
// Can have spaces; not used in any scripts
// after adding to table `source`
$source_name_full="Catálogo de las plantas vasculares del Cono Sur (Argentina, Sur de Brasil, Chile, Paraguay y Uruguay)";

// Primary url for this source (optional)
$source_url="http://www.darwin.edu.ar/Proyectos/FloraArgentina/fa.htm";	

// Load citation from bibtex file?
$citation_from_bibtex=TRUE;

// bibtext formatted citation for thsi source
// Over-ridden by bibtex file if $citation_from_bibtex==TRUE
$citation="";

// Person who provided access to source (optional)
$source_contact_name="Fernando O. Zuloaga";
$source_contact_email="fzuloaga@darwin.edu.ar";

// Date accessed
// yyyy-mm-dd format
$date_accessed="2024-09-01";

// Short list of regions covered by this source, to 250 characters
$focal_regions="Argentina, Chile, Paraguay, Uruguay and southern Brazil";

// List of countries for which this source provides comprehensive
// checklists. Spellings MUST agree with spellings in table country.
// Leave empty if none. Enter names in single quotes separated by
// commas: "'countryA','countryB','countryC'" 
$cclist_countries="
'Argentina',
'Chile',
'Paraguay',
'Uruguay'
";

// Set true if country checklist also contains comprehensive
// state checklists, else false. If true will cause all states to
// be loaded to cclist under this source.
// CRITICAL! State lists will not be treated as comprehensive
// unless this parameter=TRUE
$cclist_states_from_country=true;

////////////////////////////////////////////////////////////////
// Array of all countries covered by this checklist, not just
// comprehensive checklist countries. Spelling is critical and
// must match columns names of raw data table for parsing 
// to work
////////////////////////////////////////////////////////////////
$all_countries=array(
'Argentina',
'Chile',
'Paraguay',
'Uruguay',
'Brazil'
);


// Comprehensiveness of this source. Two options:
// 1 = comprehensive. Includes all species from focal region in focal taxon. Absence from 
//		list may indicates non-native species
// 0 = selective, not comprehensive. Not all taxa in region(s) include, absence not interpretable
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

// Taxonomic scope
//	Highest taxonomic group encompassed by this source. Can be left blank.
//	In general, this should be "tracheophytes", "embryophytes", "bryophytes",
// 	but can also be a family if this is a monographic. Currently not used, but
// included for forward compatibility. Eventually I may add capability of 
// detecting major higher taxa of each observation
$taxonomic_scope="tracheophytes";
//$taxonomic_scope="";

// Replace previous records for this source?
// VERY IMPORTANT
// Set=true to replace all previous records for this source.
// Set=false to keep existing records (name+author) and add new records only.
$replace=true;

//////////////////////////////////////////////////
// Raw data file parameters
//////////////////////////////////////////////////
// Names of files you will be importing
$file_raw = "conosur.parsed.csv";

// Directory in which data for this source are stored
$datapath = $data_dir . $source_name."/"."BIEN4.2/";		
$datapath = $data_dir . $source_name."/";		

// extension of raw data files. Must be the same for all
$file_ext = ".csv";

// names of destination mysql tables
$tbl_raw=$source_name."_raw";

// Names of important fields that can be passed as parameters
$fld_scientific_name="taxon";

//////////////////////////////////////////////////
// LOAD DATA INFILE parameters
//////////////////////////////////////////////////

// Import parameters for text file
// Needed for 'LOAD DATA INFILE' statement
// Set any variable to empty string to remove entirely
$local = " LOCAL ";	// LOCAL keyword
$fields_terminated_by = " FIELDS TERMINATED BY ',' ";
//$fields_terminated_by = " FIELDS TERMINATED BY '\t' ";
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
'conosur_raw'
";


?>
