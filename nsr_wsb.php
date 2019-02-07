<?php

////////////////////////////////////////////////////////
// Accepts batch web service requests and submits to 
// nsr_batch.php
////////////////////////////////////////////////////////

include 'params.php';
//$msg = "Processing batch api request\r\n\r\n";
//file_put_contents($LOGFILE, $msg)

// Temporary data directory
$data_dir_tmp = "/tmp/nsr/data";

// Temporary input file name
$filename_tmp = uniqid(rand(), true) . '.csv';

///////////////////////////////////
// Receive & validate the POST request
///////////////////////////////////

//Make sure that it is a POST request.
if (strcasecmp($_SERVER['REQUEST_METHOD'], 'POST') != 0) {
    throw new Exception('Request method must be POST!');
}
 
//Make sure that the content type of the POST request has been set to application/json
$contentType = isset($_SERVER["CONTENT_TYPE"]) ? trim($_SERVER["CONTENT_TYPE"]) : '';
if (strcasecmp($contentType, 'application/json') != 0) {
    throw new Exception('Content type must be: application/json');
}
 
//Receive the RAW post data.
$content = trim(file_get_contents("php://input"));
 
//Attempt to decode the incoming RAW post data from JSON.
$decoded = json_decode($content, true);

//If json_decode failed, the JSON is invalid.
if (!is_array($decoded)) {
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

// Make temporary data directory in /tmp
if (!exec('mkdir -p $data_dir_tmp')) die("ERROR: Unable to create temp data directory");

// Convert array to CSV
$file_tmp = $data_dir_tmp . $filename_tmp;
$fp = fopen($file_tmp, "w");
fputcsv($fp, $decoded);
fclose($fp);

///////////////////////////////////
// Process the file in batch mode
///////////////////////////////////



///////////////////////////////////
// Retrieve the file, convert to
// JSON and return the response
///////////////////////////////////

header('Content-type: application/json');
//echo json_encode(array('nsr_results'=>$nsr_results));
//echo $nsr_results;
echo $content;

?>