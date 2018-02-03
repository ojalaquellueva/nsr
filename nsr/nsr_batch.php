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

// Generate unique code for this batch
$batch = date("Y-m-d-G:i:s").":".str_replace(".0","",strtok(microtime()," "));

// Get db connection parameters (in ALL CAPS)
include 'params.php';
include $CONFIG_DIR.'db_configw.php';
include $batch_includes_dir.'batch_params.php';

//////////////////////////////////////////////////////
// Options
//////////////////////////////////////////////////////

$shortopts  = "";
$shortopts .= "e::"; 	// command line echo (true/on;false/off [default])
$shortopts .= "i::"; 	// interactive mode (true/on;false/off [default])
$shortopts .= "f::"; 	// file name, if provided will over-ride 
						// default name in params.inc
$shortopts .= "t::"; 	// file type (csv [default], tab)
$shortopts .= "l::"; 	// line endings (mac [default], unix, win)
$shortopts .= "r::"; 	// replace cache and re-run all species 
						// (true/on;false/off [default])

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
$inputfile = $DATADIR.$inputfilename;

// Set name of result file based on input file
$pizza = explode('.',$inputfilename);
if (count($pizza)>1) {
	$lastpiece = array_pop($pizza);
	$ext = '.'.$lastpiece;
} else {
	$ext = '';
}
$resultsfilename = str_replace($ext,'',$inputfilename) . "_nsr_results.txt";
$resultsfile = $DATADIR.$resultsfilename;

// Replace cache?
// Default=false
// If true, will re-run all observations through the NSR,
// replacing any existing values in cache
$replace_cache = false;
if (array_key_exists('r', $options)) {
	$r = $options["r"];
	if ($r === true || $r == 'true' || $r == 'on') $replace_cache = true;
}
$replace_cache===true?$replace_cache_str='true':$replace_cache_str='false';

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
Batch id: $batch

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

if(file_exists($inputfile)) {
	/* connect to the db */
	include 'db_batch_connect.php';
	
	// Import raw observations to temporary table
	include_once $batch_includes_dir."create_observation_raw.php";	
	include_once $batch_includes_dir."import_raw_observations.php";
	
	// insert raw observations
	include_once $batch_includes_dir."insert_observations.php";					
	
	// perform any standardizations needed
	
	if ($echo_on) echo "Standardizing observations...";
	include_once "standardize_observations.php";
	if ($echo_on) echo $done;	

	// Mark records already in cache
	if ($echo_on) echo "Marking observations already in cache...";
	include_once "mark_observations.php";	
	if ($echo_on) echo $done;	
	
	include 'db_batch_connect.php';
		
	// Process observations not in cache, if any, then add to cache
	// Do only if >=1 observations not in cache
	$sql="
	SELECT COUNT(*) AS rows
	FROM observation
	WHERE $BATCH_WHERE_NA 
	AND is_in_cache=0
	;
	";
	//$result = mysql_query($sql);	
	//$num_rows = mysql_num_rows($result);
	$num_rows = sql_get_first_result($sql,'rows');

	if ($num_rows>0) {
		if ($echo_on) echo "Resolving $num_rows new observations:\r\n";
		include_once "nsr.php";	
		//if ($echo_on) echo "$done";
	}
		
	// Update observation table from cache
	include_once $batch_includes_dir."update_observations.php";		
	
	// dump nsr results to text file
	include_once $batch_includes_dir."dump_nsr_results.php";			
	//exit ("Exiting...\r\n\r\n");
} else {
	die("\r\nError: file '$inputfile' not found!\r\n");
}

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
