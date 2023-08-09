<?php

//////////////////////////////////////////////////
// Include paths and filenames
//////////////////////////////////////////////////

// server_config.php in parent directory, outside repo
// Path to server_config file in config directory
// Parameters $BASE_DIR & $APP_DIR (see below) are set in this file
include dirname(__FILE__) . "/../config/server_config.php";

// dir where db user & pwd file kept
// Should be outside application directory and html directory
$CONFIG_DIR = $BASE_DIR."config/"; 

// Input & output data directory
$DATADIR = $BASE_DIR."data/user/";
//$DATADIR = $APP_DIR."data/user/";

// Path and name of log file
$LOGFILE_NAME = "log.txt";
$LOGFILE_PATH = $APP_DIR;
$LOGFILE = $LOGFILE_PATH . $LOGFILE_NAME;

// Path to general php funcions and generic include files
//$utilities_path="/home/boyle/global_utilities/php/"; // Master, testing only
$utilities_path=$APP_DIR."php_utilities/";	// Local submodule directory

// General php funcions and generic include files
include $utilities_path."functions.inc";
include $utilities_path."status_codes.inc.php";
include $utilities_path."taxon_functions.inc";
include $utilities_path."sql_functions.inc";
include $utilities_path."geo_functions.inc";
$timer_on=$utilities_path."timer_on.inc";
$timer_off=$utilities_path."timer_off.inc";

// Include files for core nsr application
$nsr_includes_dir="nsr_includes/";		// include files specific to nsr app

// Include files for batch applicaton
$batch_includes_dir="nsr_batch_includes/";	// include files specific to batch app

//////////////////////////////////////////////////
// Set to ' o.is_in_cache=0 ' to check non-
// cached observations only. Results for cached
// observations will be obtained from cache  
// (faster).
// Otherwise, set to ' 1 ' to force NSR to look up
// resolve all observations from scratch (slower)
//////////////////////////////////////////////////
//$CACHE_WHERE = " 1 ";
//$CACHE_WHERE_NA = " 1 ";	// no alias version
$CACHE_WHERE = " o.is_in_cache=0 ";
$CACHE_WHERE_NA = " is_in_cache=0 ";	// no alias version

//////////////////////////////////////////////////
// Default batch size
// Recommend 10000
//////////////////////////////////////////////////
$batch_size=10000;

/////////////////////////////////////////////////
// API parameters
/////////////////////////////////////////////////

// Return offending SQL on error? (true|false)
// TURN OFF FOR PRODUCTION! ($err_show_sql=false)
$err_show_sql=false;

// Maximum permitted input rows per request
// For no limit, set to 0
$MAX_ROWS=5000;	
					
// Number of batches
$NBATCH=10000;	
$NBATCH=25;				

//////////////////////////////////////////////////
// All NSR options
// Use to test if submitted options allowed
//////////////////////////////////////////////////

# Option "resolve" goes to nsr_batch; other options query db directly
$NSR_MODES = array("resolve", "meta", "sources", "citations", "checklist_countries", "country_checklists");

# NSR checklist sources
# Not currently used
# Consider getting these directly from database instead!
$NSR_SOURCES = array("weakly","enquist"); // ...and etc....

//////////////////////////////////////////////////
// NSR default options
//////////////////////////////////////////////////

$NSR_DEF_MODE = "resolve";		// Processing mode
$NSR_DEF_SOURCES = "weakly,enquist";	// Checklist sources

//////////////////////////////////////////////////
// MySQL import parameters for raw observation text file
// Set any variable to empty string to remove entirely
//////////////////////////////////////////////////
$local = " LOCAL ";	// LOCAL keyword

$fields_terminated_by = " FIELDS TERMINATED BY ',' ";
//$fields_terminated_by = " FIELDS TERMINATED BY '\t' ";

$optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  
//$optionally_enclosed_by = "";

// whichever of the following works will depend on the operating system
// the input file was created or modified on
//$lines_terminated_by = " LINES TERMINATED BY '\r\n' "; 	// windows line-endings
//$lines_terminated_by = " LINES TERMINATED BY '\r' "; 	// mac line-endings
$lines_terminated_by = " LINES TERMINATED BY '\n' ";	// unix line-endings

$ignore_lines = " IGNORE 1 LINES ";	// Ignore header line?
//$ignore_lines = "";	// Ignore header line?

//////////////////////////////////////////////////
// Optional run-time echo variables
// Only used if running in batch mode and runtime
// echo enabled
//////////////////////////////////////////////////
$done = "done\r\n";

?>
