<?php

////////////////////////////////////////////////////////
// Accepts batch web service requests and submits to 
// nsr_batch.php
////////////////////////////////////////////////////////

///////////////////////////////////
// Parameters
///////////////////////////////////

include 'params.php';
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

//Make sure that request is a POST
if (strcasecmp($_SERVER['REQUEST_METHOD'], 'POST') != 0) {
    throw new Exception('Request method must be POST!');
}
 
//Make sure that the content type of the POST request has been set to application/json
$contentType = isset($_SERVER["CONTENT_TYPE"]) ? trim($_SERVER["CONTENT_TYPE"]) : '';
if (strcasecmp($contentType, 'application/json') != 0) {
    throw new Exception('Content type must be: application/json');
}
 
//Receive the RAW post data.
$input_json = trim(file_get_contents("php://input"));
 
//Attempt to decode the incoming RAW post data from JSON.
$input_array = json_decode($input_json, true);

//If json_decode failed, the JSON is invalid.
if (!is_array($input_array)) {
    throw new Exception('Received content contained invalid JSON!');
}

///////////////////////////////////
// Inspect the JSON data and run 
// safety/security checks
///////////////////////////////////


///////////////////////////////////
// Convert JSON and save to data 
// directory as CSV file
///////////////////////////////////

// Make temporary data directory & file in /tmp 
$cmd="mkdir -p $data_dir_tmp";
exec($cmd, $output, $status);
if ($status) die("ERROR: Unable to create temp data directory");
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
$cmd="php nsr_batch.php -e=false -i=false -f='$filename_tmp' -d='$data_dir_tmp_full' -l=unix -t=csv -r=false";
exec($cmd, $output, $status);
if ($status) die("ERROR: php_batch non-zero exit status");

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
$results_json = json_encode($results_array);

///////////////////////////////////
// Echo the results
///////////////////////////////////

header('Content-type: application/json');
echo $results_json;

?>