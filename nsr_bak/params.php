<?php

//////////////////////////////////////////////////
// Include paths and filenames
//////////////////////////////////////////////////
// test
$BASE_DIR = "/home/boyle/nsr/";
$APP_DIR = $BASE_DIR."nsr_superbatch/nsr/";
$CONFIG_DIR = $BASE_DIR; // dir where db user & pwd file kept
$DATADIR = $BASE_DIR."data/user/";

// general php functions
$utilities_path=$BASE_DIR."../global_utilities/";
include $utilities_path."functions.inc";
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
// cached observations only. Otherwise, set to ' 1 '
//////////////////////////////////////////////////
$CACHE_WHERE = " o.is_in_cache=0 ";
$CACHE_WHERE_NA = " is_in_cache=0 ";	// no alias version

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
$lines_terminated_by = " LINES TERMINATED BY '\r' "; 	// mac line-endings
//$lines_terminated_by = " LINES TERMINATED BY '\n' ";	// unix line-endings

$ignore_lines = " IGNORE 1 LINES ";	// Ignore header line?
//$ignore_lines = "";	// Ignore header line?

//////////////////////////////////////////////////
// Optional run-time echo variables
// Only used if running in batch mode and runtime
// echo enabled
//////////////////////////////////////////////////
$done = "done\r\n";

?>
