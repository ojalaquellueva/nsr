<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

echo "Loading raw data:\r\n";

echo "  '$file_dist' --> `$tbl_dist_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_dist' 
INTO TABLE $tbl_dist_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_dist_raw))) die("Error\r\n.");
echo $done;

echo "  '$file_taxon' --> `$tbl_taxon_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_taxon' 
INTO TABLE $tbl_taxon_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_taxon_raw))) die("Error\r\n.");
echo $done;

?>
