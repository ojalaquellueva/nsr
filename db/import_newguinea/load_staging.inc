<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
//
// Omits duplicate records of the same value of taxon + poldiv. 
///////////////////////////////////////////////////////

echo "Loading raw data to staging table distribution_staging...";
$sql="
INSERT INTO distribution_staging (
source_name,
country,
state_province,
county_parish,
taxon,
taxon_rank,
native_status,
cult_status
)
SELECT
'$src',
country,
state_province,
county_parish,
taxon,
taxon_rank,
native_status,
NULL
FROM $tbl_raw_final
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>