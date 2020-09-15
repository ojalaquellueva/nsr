<?php

//////////////////////////////////////////////////////
// Assembles test batch request and submits to NSR API
// Imports names from file on local file sysytem
//////////////////////////////////////////////////////

// Load functions
require("php_utilities/functions.inc");

/////////////////////
// API parameters
/////////////////////

// Path and name of file containing input names and political divisions
$DATADIR = "data/user/";
$inputfilename = "nsr_testfile.csv";

// Number of lines to import
// Start with a very small number for testing
// Set to large number to impart entire file
$lines = 1000;

// api base url 
$base_url = "https://bien.nceas.ucsb.edu/nsr/nsr_wsb.php";	# Prod
//$base_url = "https://bien.nceas.ucsb.edu/nsrdev/nsr_wsb.php"; 	# Dev
$base_url = "https://bien.nceas.ucsb.edu/nsrdev/nsr_wsb.new.php"; 	# Dev.new

/////////////////////
// NSR options
/////////////////////

// Processing mode
//	Options: resolve*|parse|meta
// 	E.g., $mode="parse"
$mode="resolve";	# Resolve native status
//$mode="meta";		# Return metadata on NSR & sources
//$mode="sources";		# List NSR sources
$mode="citations";		# Return citations for NSR & sources

/////////////////////////////////////////
// Display options
// 
// * Turn on/off what is echoed to terminal
// * Raw data always displayed
/////////////////////////////////////////

$disp_data_array=false;		// Echo raw data as array
$disp_combined_array=false;	// Echo combined options+data array
$disp_opts_array=false;		// Echo NSR options as array
$disp_opts=true;			// Echo NSR options
$disp_json_data=false;		// Echo the options + raw data JSON POST data
$disp_results_json=true;	// Echo results as array
$disp_results_array=false;	// Echo results as array
$disp_results_csv=true;		// Echo results as CSV text, for pasting to Excel

///////////////////////////////
// Make options array
///////////////////////////////

$opts_arr = array(
"mode"=>$mode
);

///////////////////////////////
// Make data array
///////////////////////////////

if ($mode=="resolve") {
	// Import csv data and convert to array
	$data_arr = array_map('str_getcsv', file($DATADIR.$inputfilename));

	# Get subset
	$data_arr = array_slice($data_arr, 0, $lines);

	// Echo the raw data
	if ( $mode=="resolve" || $mode=="" ) {
		// Echo raw data
		echo "The raw data:\r\n";
		foreach($data_arr as $row) {
			foreach($row as $key => $value) echo "$value\t"; echo "\r\n";
		}
		echo "\r\n";

		if ($disp_data_array) {
			echo "The raw data as array:\r\n";
			var_dump($data_arr);
			echo "\r\n";
		}
	}
} else {
	$data_arr=array();
}

// // Convert to JSON
//$json_data = json_encode($data_arr);	

///////////////////////////////
// Merge options and data into 
// json object for post
///////////////////////////////

$json_data = json_encode(array('opts' => $opts_arr, 'data' => $data_arr));	

// Echo the JSON
echo "The JSON input for the API:\r\n";
echo $json_data . "\r\n\r\n";

///////////////////////////////
// Decompose the JSON into opt 
// and data (for display)
///////////////////////////////

$input_array = json_decode($json_data, true);

if ($disp_combined_array) {
	echo "The combined array:\r\n";
	var_dump($input_array);
	echo "\r\n";
}

$opts = $input_array['opts'];
if ($disp_opts_array) {
	echo "Options array:\r\n";
	var_dump($opts);
	echo "\r\n";
}

if ($disp_opts) {
	// Convert booleans to text for display
	$mode_disp = isset($opts['mode']) ? $mode : "resolve";
	
	// Echo the options
	echo "NSR options:\r\n";
	echo "  mode: " . $mode_disp . "\r\n";
	echo "\r\n";
}

if ($disp_json_data) {
	// Echo the final JSON post data
	echo "API input (options + raw data converted to JSON):\r\n";
	echo $json_data . "\r\n\r\n";
}

///////////////////////////////
// Call the API
///////////////////////////////

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

// if ( $status != 201 && $status != 200 ) {
//     die("Error: call to URL $url failed with status $status, response $response, curl_error " . curl_error($ch) . ", curl_errno " . curl_errno($ch) . "\r\n");
// }
if ( $status != 201 && $status != 200 ) {
	$status_msg = $http_status_codes[$status];
    die("Error: call to URL $url failed with status $status $status_msg \r\nDetails: $response \r\n");
}

// Close curl
curl_close($ch);

$results_json = $response;
$results = json_decode($results_json, true);

// Echo the response content
echo "API results (JSON)\r\n";
if (is_array($results_json)) {
	print_r($results_json);
} else {
	echo $results_json;
}
;
echo "\r\n\r\n";

if ($mode=="resolve") {
	echo "API results as CSV (selected fields only):\r\n";
	foreach($results as $result) {
		$flds1 =array_slice($result, 0, 1);
		$flds2 =array_slice($result, 2, 4);
		$flds3 =array_slice($result, 12, 3);
		$line = implode(",", $flds1) . "," . implode(",", $flds2) . "," . implode(",", $flds3);
		echo $line;
		echo "\r\n";
	}
	echo "\r\n";
} else if ($mode=="citations") {
	echo "API results as CSV (for pasting to spreadsheet):\r\n";

	if ( $mode=="parse" || $mode=="" ) {
		foreach($results as $result) {
			$line = implode(",", array_slice($result, 0)) . "\r\n";
			print_r($line);
		}
	} else {
		$table = array_to_csv($results,",");
		echo $table;
	}
	echo "\n";
}

?>