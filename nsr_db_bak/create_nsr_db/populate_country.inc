<?php

//////////////////////////////////////////
// Populates table country from dump of
// table country from geonames db
//////////////////////////////////////////

echo "  country...";
$sql="
LOAD DATA $local INFILE '$datapath$file_country' 
INTO TABLE country 
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '\"' 
LINES TERMINATED BY '\n'
IGNORE 1 LINES
;
";
sql_execute_multiple($sql);
echo $done;

?>