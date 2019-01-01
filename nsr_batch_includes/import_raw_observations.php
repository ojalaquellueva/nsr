<?php
// Imports raw observation file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

if ($echo_on) echo "Importing file $inputfilename to table `observation_raw`...";
$sql = "
LOAD DATA $local INFILE '$inputfile' 
INTO TABLE observation_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
//echo "\r\n$sql\r\n";
sql_execute_multiple($sql);

if (!(empty_string_to_null('observation_raw'))) die("Error\r\n.");
if ($echo_on) echo "done\r\n";

?>