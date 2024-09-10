<?php

//////////////////////////////////////////////////
//////////////////////////////////////////////////
// Loading scripts for BIEN Cultivated Species database
//
// By: Brad Boyle
// Contact: bboyle@email.arizona.edu
// Date created: 18 Feb. 2014
// Last revised: 9 Sept. 2024
//
// Notes:
// 1. Everything you need to set is here and in local
// 		params.inc file in each import directory
// 2. Read the readme files in this directory and 
// 		all main subdirectories!
// 3. Some critical but sensitive parameters such as $DB
// 		are defined the config files kept outside this repo. 
// 		Be sure to check them!
//////////////////////////////////////////////////
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// Replace database? (true/false)
//
// IMPORTANT! Set to true to replace database entirely
// all tables will be dropped and replaced with new,
// empty tables. Application will automatically prompt
// for confirmation if this option is set to true.
//
// Set to false keep existing database and
// add (if new) or replace (if already present) only
// the source(s) listed in $src_array.
//
//////////////////////////////////////////////////
$REPLACE_DB = FALSE;

//////////////////////////////////////////////////
// Distribution sources
//
// CRITICAL!!!
// Include in this array the name of every source
// you will be importing into the database
// Import scripts and data for each source MUST
// be their own directory called "import_[$sourceName]",
// for example, "import_tropicos". Source names 
// below MUST match the parameter $sourceName 
// as specified in params.inc in import subdirectory
// for that source. 
//////////////////////////////////////////////////

$src_array=array(
	"ipane",
	"weakley",
	"mab",
	"powo",
	"flbr",
	"conosur",
	"fwi",
	"mexico",
	"tropicos",
	"usda",
	"vascan",
	"newguinea"
);

/* 
$src_array=array(
	"usda"
);
 */


//////////////////////////////////////////////////
// Limit rows loaded per source?
// For testing/development using subsample of data
// Set to empty string for production (imports all)
//////////////////////////////////////////////////

# Integer # of rows to import, "" imports all
$ROW_LIMIT="";
$ROW_LIMIT=200;

//////////////////////////////////////////////////
// NSR metadata
//
// Also update source-specific metadata in parameter 
// file of each data source. E.g.,  
// "import_powo/params.inc"
//////////////////////////////////////////////////

// Overall application version
// Increments when *either* code version or
// DB version is changed
$META_APP_VERSION="3.0";

// Database version
// This should only increment when the database changes
$META_DB_VERSION="3.0";
$META_DB_VERSION_COMMENTS="Remove enquist, update powo, flbr, conosur, vascan";

// Date of the latest DB modification, however slight
// Either enter manually as "YYYY-MM-DD", or use keyword 'current'
// to set to todays date using MySQL function CURRENT_DATE()
$META_DB_MODIFIED_DATE='current';

// Date of most recent complete rebuild of entire database
// Either enter manually as "YYYY-MM-DD", or use keyword 'current'
// to set to todays date using MySQL function CURRENT_DATE()
$META_DB_FULL_BUILD_DATE='current';

// Application code version
// = tag # for latest commit associated with this DB version
$META_CODE_VERSION="3.0";
$META_CODE_VERSION_COMMENTS="Modifications to support changed schema for powo and more complete metadata";

// Date associated with most recent tagged commit
// Either enter manually as "YYYY-MM-DD", or use keyword 'current'
// to set to todays date using MySQL function CURRENT_DATE()
$META_CODE_VERSION_RELEASE_DATE="2024-08-31";

// Example citation of this application, as bibtex
$META_CITATION="@misc{nsr.app, author = {Boyle, B. L. and Maitner, B. and Barbosa, G. C. and Rethvick, S. Y. B. and Enquist, B. J.}, journal = {Botanical Information and Ecology Network}, title = {Native Species Resolver}, year = {2024}, url = {https://nsr.biendata.org/}, note = {Accessed <date_of_access>} }";

// Application publication, if any, as bibtex
$META_PUBLICATION="";

// Path to icons and image files for API web app
// Path should be relative to the API base directory
$META_LOGO_PATH="images/";

// Import current (historical) table meta from previous database?
// TRUE|FALSE
// New metadata records for new database will be inserted at the end.
// The old table MUST have and identical schema to the new one for this to work.
// If not, set $META_IMPORT=FALSE to load only the single metadata record for the 
// new database, then rebuild historical table manually after DB build is complete.
// Always set to TRUE if possible preserve metadata history
$META_IMPORT=TRUE;

// Name of previous database in which historical meta table is found
// Must be on the same server
// You MUST supply this parameter if $META_IMPORT=TRUE
$META_DB_PREV="nsr_2_0";

//////////////////////////////////////////////////
// Users & access levels
//
// IMPORTANT! These users will be granted access to
// the completed database. All usernames must already 
// exist in MySQL. This variable is an array with one
// username + access level per line, separated by pipe (|)
// and surround by double quotes, quoted elements 
// separated by commas. If you do not wish to grant any
// privileges, set to entire array to empty string "".
//
// Access levels:
//	read: SELECT only
//	write: SELECT, INSERT, UPDATE, DELETE, CREATE, DROP (tables only)
//	admin: All privileges
//////////////////////////////////////////////////

$usr_array=array(
	"nsr_read|read",
	"nsr|write"
);

//////////////////////////////////////////////////
// Paths and filenames
//////////////////////////////////////////////////

// Base directory
// All other paths are relative to this one
$base_dir = "/home/boyle/bien/";

// Base directory for all code related to this application
$app_base_dir = $base_dir . "nsr/";

// Application code directory (this one; git repo)
$app_dir = $app_base_dir . "src/db/";

// Data directory
// Keep outside repo
$data_dir = $app_base_dir . "data/db/";

// DB config file (DB name, users, passwords
// Keep outside repo
$config_dir = $app_base_dir . "config/";

// Path to general php functions and other generic include files
// Subdirectory "includes/" is a git submodule
$global_utilities_path = $base_dir . "includes/php/";

// Path to local functions not in submodule "includes"
// Recommend move to submodule once functions have 
// been tested
$local_utilities_path = $app_dir."functions/";

//////////////////////////////////////////////////
// Db connection file
//////////////////////////////////////////////////

$config_file = $config_dir . "db_config_nsr_db.inc";

///////////////////////////////////////////////////
// Include files (functions, etc.)
// These are imported as one or more
// git submodules & saved to locations shown below.
///////////////////////////////////////////////////

include $global_utilities_path."functions.inc";
include $global_utilities_path."taxon_functions.inc";
include $global_utilities_path."sql_functions.inc";
include $global_utilities_path."geo_functions.inc";
$timer_on=$global_utilities_path."timer_on.inc";
$timer_off=$global_utilities_path."timer_off.inc";
include $local_utilities_path."functions_local.inc.php";

//////////////////////////////////////////////////
// Cleanup parameters
//////////////////////////////////////////////////

// Keep the following for backwards-compatibility,  
// otherwise will have to modify import.php for 
// each source. These parameters now superseeded 
// by $TEMP_TABLE_ACTION
// Set both to FALSE
$drop_raw=FALSE;
$drop_raw_force=FALSE;

// Fate of temp tables after DB build complete
// Values: drop|move|neither
// "drop": Delete raw and staging tables
// "move": move to staging database
// "nothing": do nothing; leave all temp tables where they are
// "none": synonym of "nothing"
// Staging database will be automatically named $DB . "_staging"
$TEMP_TABLE_ACTION='move';

// Replace staging DB or move tables to existing DB?
// TRUE: Replaces staging DB, if already exists
// FALSE: Move tables into existing staging DB, if exists
//   if doesn't exist, creates new DB
$DB_STAGING_REPLACE=FALSE;

//////////////////////////////////////////////////
// API parameters
//////////////////////////////////////////////////

// GNRS base url
$gnrs_url = "http://vegbiendev.nceas.ucsb.edu:8875/gnrs_api.php"; 

//////////////////////////////////////////////////
// Error-reporting & runtime behavior
//////////////////////////////////////////////////

// echos error messages to screen
$echo_on = true;		

// aborts entire script on error
$die_on_fail = true;		

// default success and fail messages
$done = "done\r\n";
$msg_success = "done\r\n";
$msg_fail = "failed!\r\n";

?>