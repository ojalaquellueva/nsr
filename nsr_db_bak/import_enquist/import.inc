<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

echo "Loading raw data:\r\n";

echo "  Importing file $file_raw_enquist_ow_endemics to table `$tbl_raw_enquist_ow_endemics`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_enquist_ow_endemics' 
INTO TABLE $tbl_raw_enquist_ow_endemics 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_raw))) die("Error\r\n.");
echo $done;

echo "  Importing file $file_raw_enquist_cultspp to table `$tbl_raw_enquist_cultspp`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_enquist_cultspp' 
INTO TABLE $tbl_raw_enquist_cultspp 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_raw))) die("Error\r\n.");
echo $done;


?>
