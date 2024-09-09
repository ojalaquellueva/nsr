<?php

//////////////////////////////////////////
// Populates temp table gadm_admin_1_raw
//////////////////////////////////////////

echo "  gadm_admin_1_raw...";
$sql="
LOAD DATA $local INFILE '$datapath$file_gadm_state_province' 
INTO TABLE gadm_admin_1_raw 
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '\"' 
LINES TERMINATED BY '\n'
IGNORE 1 LINES
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>