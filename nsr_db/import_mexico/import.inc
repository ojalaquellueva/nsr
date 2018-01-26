<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

echo "Loading raw data:\r\n";

echo "  '$file_raw' --> `$tbl_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw' 
INTO TABLE $tbl_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_raw))) die("Error\r\n.");
echo $done;

echo "  '$file_species_raw' --> `$tbl_species_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_species_raw' 
INTO TABLE $tbl_species_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_raw))) die("Error\r\n.");
echo $done;

?>
