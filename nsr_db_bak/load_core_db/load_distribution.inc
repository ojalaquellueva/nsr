<?php

echo "  Loading table distribution...";
$sql="
INSERT INTO distribution (
source_id,
taxon_rank,
taxon,
country,
state_province,
county_parish,
native_status,
native_status_details,
cult_status
)
SELECT
$source_id,
taxon_rank,
taxon,
country,
state_province,
county_parish,
native_status,
native_status_details,
cult_status
FROM distribution_staging
;
";
sql_execute_multiple($sql);
echo $done;

?>