<?php

//////////////////////////////////////////
// Populates table state_province
//////////////////////////////////////////

echo "  state_province_name...";
$sql="
LOAD DATA $local INFILE '$datapath$file_state_province_name' 
INTO TABLE state_province_name 
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '\"' 
LINES TERMINATED BY '\n'
IGNORE 1 LINES
;
";
sql_execute_multiple($sql);
echo $done;

?>