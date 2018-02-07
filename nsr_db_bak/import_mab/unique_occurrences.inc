<?php

//////////////////////////////////////////////////
// Save unique occurrences to main raw table and 
//////////////////////////////////////////////////

echo "Extracting unique occurrences...";
$sql="
DROP TABLE IF EXISTS mab_raw_temp;
CREATE TABLE mab_raw_temp LIKE mab_raw;

INSERT INTO mab_raw_temp (
country, 
taxon,
taxon_rank,
added_by,
check_Fail,
source,
include
)
SELECT DISTINCT
country, 
taxon,
taxon_rank,
added_by,
check_Fail,
source,
include
FROM mab_raw
;
DROP TABLE mab_raw;
RENAME table mab_raw_temp to mab_raw
;
";
sql_execute_multiple($sql);
echo $done;

?>