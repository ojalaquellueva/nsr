<?php

///////////////////////////////////////////////////////////////////////////
/*
Native Status Resolver (NSR)

Basic NSR batch processing service
For each valid combination of species+country+state_province+county_parish
Returns and evaluation of native status
Return format is csv

To execute, run /var/www/bien/apps/nsr/nsr_batch.php

Input: CSV file, "nsr_input.csv" in /var/www/bien/apps/nsr/data/

Columns:
family - optional
genus - optional, but required if species present
species - required; species or lower level taxon such as variety; NO AUTHORITY
country - required
state_province - optional, but required if county_parish present
county_parish - optional
user_id - optional; INTEGER UNSIGNED

Returns: tab-delimited file, "nsr_results.txt", in /var/www/bien/apps/nsr/data/
*/ 
///////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////
// Parameters
//////////////////////////////////////////////////////

// Mode determines which database is used
$MODE = "batch";

// Generate unique code for this job
$job = date("Y-m-d-G:i:s").":".str_replace(".0","",strtok(microtime()," "));
#$job = '2018-02-03-8:50:42:0.69830700';	# Big BIEN job; save for now

// Get db connection parameters (in ALL CAPS)
include 'params.php';
include $CONFIG_DIR.'db_configw.php';
include $batch_includes_dir.'batch_params.php';

//////////////////////////////////////////////////////
// Options
//////////////////////////////////////////////////////

$shortopts  = "";
$shortopts .= "e::"; 	// command line Echo (true/on;false/off [default])
$shortopts .= "i::"; 	// Interactive mode (true/on;false/off [default])
$shortopts .= "f::"; 	// File name, if provided will over-ride 
						// default name in params.php
$shortopts .= "d::"; 	// custom Data directory, if omitted defaults to
						// value of $DATADIR set in params.php
$shortopts .= "t::"; 	// file Type (csv [default], tab)
$shortopts .= "l::"; 	// Line endings (mac [default], unix, win)
$shortopts .= "r::"; 	// Replace cache?
						// 	false|keep [default]: keep cache
						// 	replace: replace records for same taxon+locality
						// 	delete: all records; clear entire cache

// get command line arguments, if any
$options = getopt($shortopts);

// Command line echo
$echo_on = true;
if (array_key_exists('e', $options)) {
	$e = $options["e"];
	if ($e === false || $e == 'false' || $e == 'off') {
		$echo_on = false;
	} else {
		$echo_on = true;
	}
}

// Interactive mode
$interactive = false;
if (array_key_exists('i', $options)) {
	$i = $options["i"];
	if ($i === true || $i == 'true' || $i == 'on') $interactive = true;
}
if ($interactive===true) $echo_on=true;	// If interactive mode, echo MUST be on

// Data directory
$data_dir = $DATADIR;	// Default as set in params.php
if (array_key_exists('d', $options)) {
	// Over-ride default input file name from params file
	$data_dir_custom = $options["d"];
	if ($data_dir_custom<>false) {
		if (file_exists($data_dir_custom)) {
			$data_dir = $data_dir_custom;
		} else {
			// Bad directory
			die("ERROR: Directory '$data_dir_custom' does not exist\r\n");
		}
	} else {
		// No directory value supplied
		die("ERROR: No value supplied for data directory option -d\r\n");
	}
}

// Input file name
if (array_key_exists('f', $options)) {
	// Over-ride default input file name from params file
	$file = $options["f"];
	if ($file<>false) $inputfilename = $file;		
}

// Input file type
$filetype='csv';
if (array_key_exists('t', $options)) {
	$t = $options["t"];
	if($t == "tab") {
		// tab-delimitted
		// Otherwise assumes CSV, as set in params file
		$fields_terminated_by = " FIELDS TERMINATED BY '\t' ";
		$optionally_enclosed_by = " ";  
		$filetype='tab-delimited';
	}	
}

// Input file line endings
if (array_key_exists('l', $options)) {
	// By default assumes mac line endings,
	// as set in params file
	$l = $options["l"];
	switch ($l) {
		case "unix":
			// Unix
			$lines_terminated_by = " LINES TERMINATED BY '\n' ";
			break;
		case "win":
			// Windows
			$lines_terminated_by = " LINES TERMINATED BY '\r\n' ";
			break;
	}	
}

// parameters $inputfilename and $resultsfilename in 
// batch_params.php, but can
$inputfile = $data_dir.$inputfilename;

// Set name of result file based on input file
$pizza = explode('.',$inputfilename);
if (count($pizza)>1) {
	$lastpiece = array_pop($pizza);
	$ext = '.'.$lastpiece;
} else {
	$ext = '';
}
$resultsfilename = str_replace($ext,'',$inputfilename) . "_nsr_results.txt";
$resultsfile = $data_dir.$resultsfilename;

// Replace cache?
// Default=false
// If true, will re-run all observations through the NSR,
// replacing any existing values in cache
if (array_key_exists('r', $options)) {
	$r = $options["r"];
	if ($r == 'replace' ) {
		$replace_cache = 'replace';
	} elseif ($r == 'delete' ) {
		$replace_cache = 'delete';
	} elseif ($r == 'f' || $r == 'false' || $r == 'keep') {
		$replace_cache = false;
	} else {
		die("ERROR: Invalid cache option -r=".$r."\r\n");	
	}
} else {
	$replace_cache = false;
}
$replace_cache_str=($replace_cache===false?'false':$replace_cache);

//////////////////////////////////////////////////////
// Confirm operation and connect to database
//////////////////////////////////////////////////////

if ($interactive) {
	$msg = "
Run NSR batch application with following parameters:
	
NSR database: $DB
Input file: $inputfilename
File type: $filetype
Results file: $resultsfilename
Replace cache: $replace_cache_str
Job id: $job

Enter Y to proceed, N to cancel: "
	;
	$proceed=responseYesNoDie($msg);
	if ($proceed===false) die("\r\nOperation cancelled\r\n");
}

if ($echo_on) {
	// Start timer and connect to mysql
	echo "\r\n*********Begin operation*********\r\n\r\n";
	include $timer_on;
}

//////////////////////////////////////////////////////
// Process the file
//////////////////////////////////////////////////////

if (!file_exists($inputfile)) die("\r\nError: file '$inputfile' not found!\r\n");

/* connect to the db */
include 'db_batch_connect.php';

// Import raw observations to temporary table
include_once $batch_includes_dir."create_observation_raw.php";	
include_once $batch_includes_dir."import_raw_observations.php";

// insert raw observations
include_once $batch_includes_dir."insert_observations.php";					

// perform any standardizations needed

if ($replace_cache=='replace') {
	// Remove cached observations for these species+poldiv combinations
	if ($echo_on) echo "Removing previous observations from cache...";
	include_once "remove_observations_from_cache.php";
	if ($echo_on) echo $done;	
} elseif ($replace_cache=='delete') {
	// Remove cached observations for these species+poldiv combinations
	if ($echo_on) echo "Deleting all observations from cache...";
	include_once "clear_cache.php";
	if ($echo_on) echo $done;	
} else {
	// Mark records already in cache
	if ($echo_on) echo "Marking observations already in cache...";
	include_once "mark_observations.php";	
	if ($echo_on) echo $done;	
}

include 'db_batch_connect.php';
	
// Process observations not in cache, if any, then add to cache
// Do only if >=1 observations not in cache
$sql="
SELECT COUNT(*) AS rows
FROM observation
WHERE $JOB_WHERE_NA 
AND is_in_cache=0
;
";
//$result = mysqli_query($dbh, $sql);	
//$num_rows = mysqli_num_rows($result);
$num_rows = sql_get_first_result($dbh, $sql,'rows');

if ($num_rows>0) {
	if ($echo_on) echo "Resolving $num_rows new observations in batches of $batch_size:\r\n";
	
	// Calculate number of batches
	$batches = $num_rows / $batch_size;
	$whole = intval( $batches );
	
	if ( $batches <= 1 ) {
		$batches = 1;
	} elseif ( $batches > $whole ) {
		$batches = $whole + 1;
	}
	
	$batch = 1;
	$msg1 = "  Batch 1 of $batches...marking...";
	$msg2 = "  Batch 1 of $batches...marking...processing...";
	if ($echo_on) echo $msg1;
	
	while ( $batch <= $batches ) { 
	
		if ($echo_on) echo "\r" . $msg1;
		
		// Mark the current batch
		include "dbw2_open.php";
		$sql="
		UPDATE observation
		SET batch=$batch
		WHERE $JOB_WHERE_NA 
		AND is_in_cache=0 
		AND batch IS NULL
		LIMIT $batch_size
		";
		sql_execute_multiple($dbw2, $sql);
		mysqli_close($dbw2);
	
		if ($echo_on) echo "\r" . $msg2;
		
		// Turn off echo for NSR processes
		//$echo_on = false;
		
		// Submit the current batch to NSR, reporting time if echo on
		$start_batch = microtime(true);
		include "nsr.php";	
		$end_batch = microtime(true);
		$batch_sec = round( $end_batch - $start_batch, 2);
		$batch_time = secondsToTime($batch_sec);
		
		// Turn echo back on if applicable
		if ($e === true || $e == 'true' || $e == 'on') $echo_on = true;
		
		$msg2 = "  Batch $batch of $batches...marking...processing...done ($batch_sec sec)";
		if ($echo_on) echo "\r" . $msg2;
		
		$batch++;
	}
}
if ($echo_on) echo "\n";
	
// Update observation table from cache
include_once $batch_includes_dir."update_observations.php";		

// dump nsr results to text file
include_once $batch_includes_dir."dump_nsr_results.php";			
//exit ("Exiting...\r\n\r\n");

// Clear observation table
include_once "clear_observations.php";		


//////////////////////////////////////////////////////
// Close connection and report time 
//////////////////////////////////////////////////////

if ($echo_on) {
	include $timer_off;
	$msg = "\r\n********* Operation completed *********";
	$msg = $msg . "\r\nCurrent time: ". $curr_time;
	$msg = $msg . "\r\nTime elapsed: " . $tsecs . " seconds.\r\n"; 

	echo $msg . "\r\n\r\n"; 
}

?>
