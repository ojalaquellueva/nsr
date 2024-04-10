<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

echo "Loading raw data:\r\n";

$data_raw="$datapath$file_raw";
if ( ! $ROW_LIMIT=="" ) {
	$data_raw_sample = $datapath . "raw_data_sample";
	$cmd="head -{$ROW_LIMIT} $datapath$file_raw > $data_raw_sample";	
	//echo "Running command: '" . $cmd . "'\n";
	exec($cmd, $output, $status);
	if ($status) die("ERROR: command \'{$cmd}\' failed (" . basename(__FILE__) . ")\n");	
	$data_raw=$data_raw_sample;
}

echo "  `$tbl_raw`...";
$sql = "
LOAD DATA $local INFILE '$data_raw' 
INTO TABLE $tbl_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Setting empty strings to NULL...";
if (!(empty_string_to_null($dbh, $tbl_raw))) die("Error\r\n.");
echo $done;
echo "    Setting NA to NULL...";
if (!(NA_to_null($dbh, $tbl_raw))) die("Error\r\n.");
echo $done;

?>
