<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by
// and $ignore_lines are set in parameters file
// NOTE: didn't implement $ROW_LIMIT for this source due to small size and 
//   liklihood of broken links between the many tables

echo "Loading raw data:\r\n";

echo "  Importing file $file_raw_weakley_exotic_part to table `$tbl_weakley_exotic_part_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_weakley_exotic_part' 
INTO TABLE $tbl_weakley_exotic_part_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
if (!(empty_string_to_null($dbh, $tbl_raw))) die("Error\r\n.");
echo $done;

echo "  Importing file $file_raw_weakley_exotic_all to table `$tbl_weakley_exotic_all_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_weakley_exotic_all' 
INTO TABLE $tbl_weakley_exotic_all_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
if (!(empty_string_to_null($dbh, $tbl_raw))) die("Error\r\n.");
echo $done;

echo "  Importing file $file_raw_weakley_origin to table `$tbl_weakley_origin_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_weakley_origin' 
INTO TABLE $tbl_weakley_origin_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
if (!(empty_string_to_null($dbh, $tbl_raw))) die("Error\r\n.");
echo $done;

echo "  Importing file $file_raw_weakley_poldivs to table `$tbl_weakley_poldivs_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_weakley_poldivs' 
INTO TABLE $tbl_weakley_poldivs_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
if (!(empty_string_to_null($dbh, $tbl_raw))) die("Error\r\n.");
echo $done;


?>
