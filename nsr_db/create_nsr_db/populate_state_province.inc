<?php

//////////////////////////////////////////
// Populates table state_province
//////////////////////////////////////////

echo "  state_province...";
$sql="
LOAD DATA $local INFILE '$datapath$file_state_province' 
INTO TABLE state_province 
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '\"' 
LINES TERMINATED BY '\n'
IGNORE 1 LINES
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>