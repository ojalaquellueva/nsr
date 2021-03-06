<?php

//////////////////////////////////////////////////////
// Assembles test batch request and submits to NSR API
// Imports names from file on local file sysytem
//////////////////////////////////////////////////////

/////////////////////
// Parameters
/////////////////////

// Path and name of file containing input names and political divisions
$DATADIR = "data/user/";
$inputfilename = "nsr_testfile.csv";

// Number of lines to import
// Start with a very small number for testing
// Set to large number to impart entire file
$lines = 1000;

// api base url 
$base_url = "https://bien.nceas.ucsb.edu/nsr/nsr_wsb.php";
$base_url = "https://bien.nceas.ucsb.edu/nsrdev/nsr_wsb.php"; 	# Dev

/////////////////////
// Functions
/////////////////////

function csvtoarray($file,$delimiter,$lines) {
	///////////////////////////////////////////////
	// Import CSV to array, keeping only the 
	// specified number of lines
	///////////////////////////////////////////////
	
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
    
    return $f_array;
}

/////////////////////
// Main
/////////////////////

// Import the csv data as an array
$inputfile = $DATADIR.$inputfilename;
$data = csvtoarray($inputfile, ",",$lines);

# Convert to JSON
$json_data = json_encode($data);	

// Echo the raw data
echo "The raw data:\r\n";
foreach($data[0] as $key => $value) echo "$key\t"; echo "\r\n";
foreach($data as $row) {
	foreach($row as $key => $value) echo "$value\t"; echo "\r\n";
}
echo "\r\n\r\n";

// Echo the JSON
echo "The JSON input for the API:\r\n";
echo $json_data . "\r\n\r\n";

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

$results_json = $response;
$results = json_decode($results_json, true);

// Echo the response content
echo "JSON response:\r\n";
echo $results_json;
echo "\r\n\r\n";

echo "Response as CSV (selected fields only):\r\n";
foreach($results as $result) {
	$flds1 =array_slice($result, 0, 1);
	$flds2 =array_slice($result, 2, 4);
	$flds3 =array_slice($result, 12, 3);
	$line = implode(",", $flds1) . "," . implode(",", $flds2) . "," . implode(",", $flds3);
	echo $line;
    echo "\r\n";
}
echo "\r\n";

?>