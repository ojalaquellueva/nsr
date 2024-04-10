<?php

/////////////////////////////////////////////////////////////
// Loads raw observations to table observation 
/////////////////////////////////////////////////////////////

echo "Importing file $file_raw to table `observation`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw' 
INTO TABLE observation 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Converting empty strings to NULL...";
if (!(empty_string_to_null($dbh, 'observation'))) die("\r\nFailed to set empty strings to NULL!\r\n");
echo $done;


?>