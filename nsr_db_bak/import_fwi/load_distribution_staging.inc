<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
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
native_status_details,
cult_status
)
SELECT DISTINCT
'$src',
country,
state_province,
county_parish,
taxon,
taxon_rank,
native_status,
native_status_details,
cult_status
FROM fwi_raw_final
;
";
sql_execute_multiple($sql);
echo $done;

?>