<?php

////////////////////////////////////////////////////////
// Accepts batch web service requests and submits to 
// nsr_batch.php
////////////////////////////////////////////////////////

$msg = "Processing batch api request\r\n\r\n";
file_put_contents($LOGFILE, $msg)

//Make sure that it is a POST request.
if(strcasecmp($_SERVER['REQUEST_METHOD'], 'POST') != 0){
    throw new Exception('Request method must be POST!');
}
 
//Make sure that the content type of the POST request has been set to application/json
$contentType = isset($_SERVER["CONTENT_TYPE"]) ? trim($_SERVER["CONTENT_TYPE"]) : '';
if(strcasecmp($contentType, 'application/json') != 0){
    throw new Exception('Content type must be: application/json');
}
 
//Receive the RAW post data.
$content = trim(file_get_contents("php://input"));
 
//Attempt to decode the incoming RAW post data from JSON.
$decoded = json_decode($content, true);
 
//If json_decode failed, the JSON is invalid.
if(!is_array($decoded)){
    throw new Exception('Received content contained invalid JSON!');
}

/*
Do some stuff here to process the request
*/

// Some bogus results
$nsr_results="
[
	{
		'name': 'Aragorn',
		'race': 'Human'
	},	
	{
		'name': 'Legolas',
		'race': 'Elf'
	},
	{
		'name': 'Gimli',
		'race': 'Dwarf'
	}
]
";

// Return the response
header('Content-type: application/json');
//echo json_encode(array('nsr_results'=>$nsr_results));
echo $nsr_results;


>?