<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
///////////////////////////////////////////////////////

echo "Loading raw data to staging table distribution_staging...";
$sql="
INSERT INTO distribution_staging (
source_name,
country,
taxon,
taxon_rank,
native_status,
cult_status
)
SELECT DISTINCT
'$src',
country,
taxon,
taxon_rank,
native_status,
NULL
FROM $tbl_raw
;
";
sql_execute_multiple($sql);
echo $done;

?>