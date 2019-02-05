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

// Number of lines to import
// Set to large number to impart entire file
$lines = 11;

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

$inputfile = $DATADIR.$inputfilename;
$json_result = csvtojson($inputfile, ",",$lines);

echo "The JSON:\r\n";
echo $json_result . "\r\n";

// Call the batch api
echo "Calling the api:\r\n";
$url = $base_url;    
$content = $json_result;

/*
$curl = curl_init($url);
curl_setopt($curl, CURLOPT_HEADER, false);
curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
curl_setopt($curl, CURLOPT_HTTPHEADER,
        array("Content-type: application/json"));
curl_setopt($curl, CURLOPT_POST, true);
curl_setopt($curl, CURLOPT_POSTFIELDS, $content);

$json_response = curl_exec($curl);

$status = curl_getinfo($curl, CURLINFO_HTTP_CODE);

if ( $status != 201 ) {
    die("Error: call to URL $url failed with status $status, response $json_response, curl_error " . curl_error($curl) . ", curl_errno " . curl_errno($curl));
}

curl_close($curl);

$response = json_decode($json_response, true);
*/


$options = array(
  'http' => array(
    'method'  => 'POST',
    'content' => $content,
    'header'=>  "Content-Type: application/json\r\n" .
                "Accept: application/json\r\n"
    )
);

$context  = stream_context_create( $options );
$result = file_get_contents( $url, false, $context );
$response = json_decode( $result );

echo $response . "\r\n";

?>