<?php

////////////////////////////////////////////////////////
// Accepts batch web service requests and submits to 
// nsr_batch.php
////////////////////////////////////////////////////////

// For testing
$cmd='echo "$(whoami)"';
exec($cmd, $output, $status);
$whoami=$output[0];
//die("whoami: '$whoami'");

///////////////////////////////////
// Parameters
///////////////////////////////////

include 'params.php';
require_once("includes/php/status_codes.inc.php");

//$msg = "Processing batch api request\r\n\r\n";
//file_put_contents($LOGFILE, $msg)

// Temporary data directory
$data_dir_tmp = "/tmp/nsr";

// Input file name
$basename = uniqid(rand(), true);
$filename_tmp = $basename . '.csv';

// Results file name
$results_filename = $basename . "_nsr_results.txt";

///////////////////////////////////
// Functions
///////////////////////////////////

// Load a tab separated text file as array
// Use option $load_keys=true only if file has header
function load_tabbed_file($filepath, $load_keys=false) {
    $array = array();
 
    if (!file_exists($filepath)){ return $array; }
    $content = file($filepath);
 
    for ($x=0; $x < count($content); $x++){
        if (trim($content[$x]) != ''){
            $line = explode("\t", trim($content[$x]));
            if ($load_keys){
                $key = array_shift($line);
                $array[$key] = $line;
            }
            else { $array[] = $line; }
        }
    }
    return $array;
}

///////////////////////////////////
// Receive & validate the POST request
///////////////////////////////////

// Start by assuming no errors
// Any run time errors and this will be set to true
$err_code=0;
$err_msg="";
$err=false;

// Make sure that request is a POST
// if (strcasecmp($_SERVER['REQUEST_METHOD'], 'POST') != 0) {
//     throw new Exception('Request method must be POST!');
// }
if (strcasecmp($_SERVER['REQUEST_METHOD'], 'POST') != 0) {
	$err_msg="ERROR: Request method must be POST\r\n"; 
	$err_code=400; goto err;
}
 
// Make sure that the content type of the POST request has been 
// set to application/json
$contentType = isset($_SERVER["CONTENT_TYPE"]) ? trim($_SERVER["CONTENT_TYPE"]) : '';
if (strcasecmp($contentType, 'application/json') != 0) {
	$err_msg="ERROR: Content type must be: application/json\r\n"; 
	$err_code=400; goto err;
}
 
// Receive the RAW post data.
$input_json = trim(file_get_contents("php://input"));
 
///////////////////////////////////////////
// Convert post data to array and separate
// data from options
///////////////////////////////////////////

//Attempt to decode the incoming RAW post data from JSON.
$input_array = json_decode($input_json, true);

// If json_decode failed, the JSON is invalid.
if (!is_array($input_array)) {
	$err_msg="ERROR: Received content contained invalid JSON!\r\n";	
	$err_code=400; goto err;
}

///////////////////////////////////
// Inspect the JSON data and run 
// safety/security checks
///////////////////////////////////

// UNDER CONSTRUCTION!

///////////////////////////////////////////
// Extract & validate options
///////////////////////////////////////////

// Get options and data from JSON
if ( ! ( $opt_arr = isset($input_array['opts'])?$input_array['opts']:false ) ) {
	$err_msg="ERROR: No options specified (element 'opts' in JSON request missing)\r\n";	
	$err_code=400; goto err;
}

///////////////////////////////////////////
// Validate options and assign each to its 
// own parameter
///////////////////////////////////////////

include $APP_DIR . "validate_options.php";
if ($err) goto err;

///////////////////////////////////////////
// Check option $mode
// If "meta", ignore other options and begin
// processing metadata request. Otherwise 
// continue processing TNRSbatch request
///////////////////////////////////////////

if ( $mode=="resolve" || $mode=="" ) { 	// BEGIN mode_if
	// nsr_batch
	
	///////////////////////////////////////////
	// Extract & validate data
	///////////////////////////////////////////

	// Get data from JSON
	if ( !( $data_arr = isset($input_array['data'])?$input_array['data']:false ) ) {
		$err_msg="ERROR: No data (element 'data' in JSON request)\r\n";	
		$err_code=400; goto err;
	}

	# Check request size
	$rows = count($data_arr);
	if ( $rows>$MAX_ROWS && $MAX_ROWS>0 ) {
		$err_msg="ERROR: Requested $rows rows exceeds $MAX_ROWS row limit\r\n";	
		$err_code=413;	# 413 Payload Too Large
		goto err; 
	}

	# Valid data array structure
	# Should have 1 or more rows of exactly 5 elements each
	$rows=0;
	foreach ($data_arr as $row) {
		$rows++;
		$values=0;
		foreach($row as $value) $values++;
		if ($values<>5) {
			$err_msg="ERROR: Data has wrong number of columns, should be exactly 5\r\n"; $err_code=400; goto err;
		}
	}
	if ($rows==0) {
		$err_msg="ERROR: No data rows!\r\n"; $err_code=400; goto err; 
	}

	///////////////////////////////////
	// Convert JSON and save to data 
	// directory as CSV file
	///////////////////////////////////

	// Make temporary data directory & file in /tmp 
	$cmd="mkdir -p $data_dir_tmp";
	exec($cmd, $output, $status);
	if ($status) die("ERROR: Unable to create temp data directory (whoami='$whoami')");
	$file_tmp = $data_dir_tmp . "/" . $filename_tmp;

	// Convert array to CSV & save
	$fp = fopen($file_tmp, "w");
	$i = 0;
	foreach ($input_array as $row) {
		if($i === 0) fputcsv($fp, array_keys($row));	// header
		fputcsv($fp, array_values($row));				// data
		$i++;
	}
	fclose($fp);

	///////////////////////////////////
	// Process the CSV file in batch mode
	///////////////////////////////////

	$data_dir_tmp_full = $data_dir_tmp . "/";
	$cmd="php nsr_batch.php -e=false -i=false -f='$filename_tmp' -d='$data_dir_tmp_full' -l=unix -t=csv -r=true";

	exec($cmd, $output, $status);
	if ($status) {
		$err_msg="ERROR: nsr_batch exit status: $status\r\n";
		$err_code=500; goto err;
	}

	///////////////////////////////////
	// Retrieve the tab-delimited results
	// file and convert to JSON
	///////////////////////////////////

	/*
	header('Content-type: application/json');echo "\r\n\$data_dir_tmp: " . $data_dir_tmp . "\r\n\r\n";
	die();
	*/

	// Import the results file (tab-delimitted)
	$results_file = $data_dir_tmp . "/" . $results_filename;
	$results_array = load_tabbed_file($results_file, true);

} elseif ( $mode=="meta" ) { // CONTINUE mode_if 
	$sql="
	SELECT db_version, build_date, code_version
	FROM meta
	;
	";
	include("qy_db.php");
} elseif ( $mode=="sources" ) { // CONTINUE mode_if 
	$sql="
	SELECT source_id, source_name, source_name_full, source_url,
	date_accessed, is_comprehensive
	FROM source
	;
	";
	include("qy_db.php");
} elseif ( $mode=="citations" ) { // CONTINUE mode_if 
	$sql="
	SELECT source_id, source_name, source_citation
	FROM source
	WHERE source_citation IS NOT NULL AND TRIM(source_citation)<>''
	;
	";
	include("qy_db.php");
}	// END mode_if

$results_json = json_encode($results_array);

///////////////////////////////////
// Echo the results
///////////////////////////////////

header('Content-type: application/json');
echo $results_json;

///////////////////////////////////
// Error: return http status code
// and error message
///////////////////////////////////

err:
http_response_code($err_code);
echo $err_msg;

?>