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

include 'params.php';	// includes html statuscodes

//$msg = "Processing batch api request\r\n\r\n";
//file_put_contents($LOGFILE, $msg)

// Temporary data directory
$data_dir_tmp = "/tmp/nsr";

// Input file name
$basename = uniqid(rand(), true);
$filename_tmp = $basename . '.csv';

// Results file name
$results_filename = $basename . "_nsr_results.tsv";

///////////////////////////////////
// Functions
///////////////////////////////////

function load_tabbed_file($filepath, $load_keys=false) {
	//////////////////////////////////////////////////////
	// Load a tab separated text file as array
	// Use option $load_keys=true only if file has header
	//////////////////////////////////////////////////////

    $array = array();
 
    if (!file_exists($filepath)){ return $array; }
//     if (!file_exists($filepath)){ 
//     	return "ERROR! File $filepath not found"; 
//     }
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

function send_response($status, $body) {
	/////////////////////////////////////////////////////
	// Send the POST response, with either data or error 
	// message in body. Body MUST be json.
	// 'Access-Control-Allow-Origin' enables CORS
	/////////////////////////////////////////////////////

	header("Access-Control-Allow-Origin: *");
	header('Content-type: application/json');
	http_response_code($status);
	echo $body;
}



///////////////////////////////////
// Receive & validate the POST request
///////////////////////////////////

// Start by assuming no errors
// Any run time errors and this will be set to true
$err_code=0;
$err_msg="";
$err=false;

// Must be pre-flight request or POST
if ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
	// Send pre-flight response and quit
	//header("Access-Control-Allow-Origin: http://localhost:3000");	// Dev
	header("Access-Control-Allow-Origin: *"); // Production
	header("Access-Control-Allow-Methods: POST, OPTIONS");
	header("Access-Control-Allow-Headers: Content-type");
	header("Access-Control-Max-Age: 86400");
	exit;
} else if (strcasecmp($_SERVER['REQUEST_METHOD'], 'POST') != 0) {
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
	$err_msg="ERROR: Received content contains invalid JSON!\r\n";	
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

// Get options from JSON
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

	# Validate data array structure
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
	
	///////////////////////////////////////////
	// Save data array as CSV file,
	// to be used as input for NSR batch 
	///////////////////////////////////////////

	// Make temporary data directory & file in /tmp 
	$cmd="mkdir -p $data_dir_tmp";
	exec($cmd, $output, $status);
	if ($status) die("ERROR: Unable to create temp data directory (whoami='$whoami')");
	$file_tmp = $data_dir_tmp . "/" . $filename_tmp;

	// Convert array to CSV & save
	$fp = fopen($file_tmp, "w");
	$i = 0;
	foreach ($data_arr as $row) {
		if($i === 0) fputcsv($fp, array_keys($row));	// header
		fputcsv( $fp, array_values($row) );				// data
		$i++;
	}
	fclose($fp);

	///////////////////////////////////
	// Process the CSV file in batch mode
	///////////////////////////////////

	$data_dir_tmp_full = $data_dir_tmp . "/";
	$cmd="php nsr_batch.php -e=false -i=false -f='$filename_tmp' -d='$data_dir_tmp_full' -l=unix -t=csv -r=false";

	// Execute the nsr_batch command
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
	SELECT app_version, db_version, db_version_comments, 
	db_version_build_date, db_full_build_date,
	code_version, code_version_release_date, code_version_comments,
	citation, publication, logo_path 
	FROM meta
	WHERE id=(SELECT MAX(id) FROM meta)
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
	SELECT 'nsr.app' AS source, citation
	FROM meta
	WHERE id=(SELECT MAX(id) FROM meta)
	UNION ALL
	-- SELECT 'nsr.pub' AS source, publication AS citation
	-- FROM meta
	-- WHERE id=(SELECT MAX(id) FROM meta)
	-- UNION ALL
	SELECT source_name AS source, citation
	FROM source
	WHERE citation IS NOT NULL AND TRIM(citation)<>''
	;
	";
	include("qy_db.php");
} elseif ( $mode=="country_checklists" ) { // CONTINUE mode_if 
	$sql="
	SELECT ps.gid_0, ps.country, group_concat(s.source_name) AS sources 
	FROM poldiv_source ps JOIN `source` s ON ps.source_id=s.source_id 
	WHERE ps.poldiv_type='country' 
	GROUP BY ps.gid_0, ps.country 
	ORDER BY ps.country
	;
	";
	include("qy_db.php");
} elseif ( $mode=="checklist_countries" ) { // CONTINUE mode_if 
	$sql="
	SELECT s.source_id, s.source_name, s.source_name_full as checklist_details, 
	s.date_accessed, s.citation AS source_citation,
	group_concat(ps.poldiv_name) AS countries
	FROM poldiv_source ps JOIN `source` s ON ps.source_id=s.source_id 
	WHERE ps.poldiv_type='country' 
	GROUP BY s.source_id
	ORDER BY s.source_id, s.source_name
	;
	";
	include("qy_db.php");
}	// END mode_if

///////////////////////////////////
// Prepare the JSON response 
///////////////////////////////////

$results_json = json_encode($results_array);

# Special handling for bibtex newlines
if ($mode=="citations") {
	$results_json = str_replace('\\n','\\\\n',$results_json);
}

///////////////////////////////////
// Send the response
///////////////////////////////////

// Status ($err_code) should be 200
send_response($err_code, $results_json);
exit;

///////////////////////////////////
// Error: return http status code
// and error message
///////////////////////////////////

err:
http_response_code($err_code);
echo $err_msg;

?>
