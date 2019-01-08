<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

echo "Loading raw data:\r\n";

echo "  Importing file $file_raw_vascan_distribution to table `$tbl_vascan_distribution_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_vascan_distribution' 
INTO TABLE $tbl_vascan_distribution_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
if (!(empty_string_to_null($dbh, $tbl_raw))) die("Error\r\n.");
echo $done;

echo "  Importing file $file_raw_vascan_taxon to table `$tbl_vascan_taxon_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_vascan_taxon' 
INTO TABLE $tbl_vascan_taxon_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
if (!(empty_string_to_null($dbh, $tbl_raw))) die("Error\r\n.");
echo $done;

?>
