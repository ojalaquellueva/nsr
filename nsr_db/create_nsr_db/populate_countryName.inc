<?php

//////////////////////////////////////////
// Populates table countryName
//////////////////////////////////////////

echo "Populating political division tables:\r\n";

echo "  countryName...";
$sql="
LOAD DATA $local INFILE '$datapath$file_country_name' 
INTO TABLE $tbl_country 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>