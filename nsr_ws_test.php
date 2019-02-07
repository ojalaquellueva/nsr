<?php

//////////////////////////////////////////////////////
// Assembles test batch request and submits to NSR API
// Imports names from file on local file sysytem
//////////////////////////////////////////////////////

/////////////////////
// Parameters
/////////////////////

// Path and name of file containing input names and political divisions
$DATADIR = "/home/boyle/nsr/data/user/";
$inputfilename = "nsr_submitted_dev2.csv";
$inputfilename = "testfile.csv";

// Desired response format, json or xml
// NOT USED YET
$format="json";

// Number of lines to import
// Set to large number to impart entire file
$lines = 100000;

// api base url 
$base_url = "http://bien.nceas.ucsb.edu/bien/apps/nsr/nsr_wsb.php";

/////////////////////
// Functions
/////////////////////

function csvtojson($file,$delimiter,$lines)
{
    if (($handle = fopen($file, "r")) === false) {
    	die("can't open the file.");
    }

    $f_csv = fgetcsv($handle, 4000, $delimiter);
    $f_array = array();

    while ($row = fgetcsv($handle, 4000, $delimiter)) {
            $f_array[] = array_combine($f_csv, $row);
    }

    fclose($handle);
    
    // Get subset of array
    $f_array = array_slice($f_array, 0, $lines);
    
    // Convert and return the JSON
    return json_encode($f_array);
}

/////////////////////
// Main
/////////////////////

// Turn the format parameter into an array
// NOT USED YET
$format_array = array("format"=>"$format");

// Import the csv data and convert a sample of it to JSON
$inputfile = $DATADIR.$inputfilename;
$json_data = csvtojson($inputfile, ",",$lines);

// Echo the input
//echo "The JSON input data:\r\n";
//echo $json_data . "\r\n";

// Call the batch api
$url = $base_url;    
$content = $json_data;

// Initialize curl & set options
$ch = curl_init($url);	
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);	// Return response (CRITICAL!)
curl_setopt($ch, CURLOPT_POST, 1);	// POST request
curl_setopt($ch, CURLOPT_POSTFIELDS, $json_data);	// Attach the encoded JSON
curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json')); 

// Execute the curl API call
$response = curl_exec($ch);

// Check status of the response and echo if error
$status = curl_getinfo($ch, CURLINFO_HTTP_CODE);

if ( $status != 201 && $status != 200 ) {
    die("Error: call to URL $url failed with status $status, response $response, curl_error " . curl_error($ch) . ", curl_errno " . curl_errno($ch) . "\r\n");
}

// Close curl
curl_close($ch);

// Echo the response content
echo "The response:\r\n";
var_dump($response);

?>