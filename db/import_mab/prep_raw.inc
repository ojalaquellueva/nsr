<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

echo "Loading raw data:\r\n";

echo "  Importing file $file_raw to table `$tbl_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw' 
INTO TABLE $tbl_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
if (!(empty_string_to_null($dbh, $tbl_raw))) die("Error\r\n.");
echo $done;

?>
