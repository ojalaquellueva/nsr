<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

echo "Loading raw data:\r\n";

// Old World endemics
$file_raw=$file_raw_enquist_ow_endemics;
$tbl_raw_tmp=$tbl_raw_enquist_ow_endemics;
echo "  '$file_raw' --> `$tbl_raw_tmp`...";

$data_raw="$datapath$file_raw";
if ( ! $ROW_LIMIT=="" ) {
	$data_raw_sample = $datapath . "raw_data_sample";
	$cmd="head -{$ROW_LIMIT} $datapath$file_raw > $data_raw_sample";	
	exec($cmd, $output, $status);
	if ($status) die("ERROR: command \'{$cmd}\' failed (" . basename(__FILE__) . ")\n");	
	$data_raw=$data_raw_sample;
}

$sql = "
LOAD DATA $local INFILE '$data_raw' 
INTO TABLE $tbl_raw_tmp 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
if (!(empty_string_to_null($dbh, $tbl_raw_tmp))) die("Error\r\n.");
echo $done;

// Cultivated species
$file_raw=$file_raw_enquist_cultspp;
$tbl_raw_tmp=$tbl_raw_enquist_cultspp;
echo "  '$file_raw' --> `$tbl_raw_tmp`...";

$data_raw="$datapath$file_raw";
if ( ! $ROW_LIMIT=="" ) {
	$data_raw_sample = $datapath . "raw_data_sample";
	$cmd="head -{$ROW_LIMIT} $datapath$file_raw > $data_raw_sample";	
	exec($cmd, $output, $status);
	if ($status) die("ERROR: command \'{$cmd}\' failed (" . basename(__FILE__) . ")\n");	
	$data_raw=$data_raw_sample;
}

$sql = "
LOAD DATA $local INFILE '$data_raw' 
INTO TABLE $tbl_raw_tmp 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
if (!(empty_string_to_null($dbh, $tbl_raw_tmp))) die("Error\r\n.");
echo $done;


?>
