<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
//
// Omits duplicate records of the same value of taxon 
// + country. Adds status codes from the first of a
// set of multiple country+taxon records. Perhaps run
// manual check to make sure this is not a problem.
///////////////////////////////////////////////////////

echo "Loading raw data to staging table distribution_staging:\r\n";

echo "  Inserting records...";
$sql="
INSERT INTO distribution_staging (
source_name,
country,
state_province,
taxon,
taxon_rank,
native_status,
cult_status
)
SELECT DISTINCT
'$src',
country,
stateProvince,
taxon,
taxon_rank,
native_status,
'unknown'
FROM `$tbl_raw`
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>