<?php

echo "Inserting comprehensive country checklists...";

$sql="
INSERT INTO fwi_raw_final (
source_name,
country,
state_province,
county_parish,
family,
genus,
species,
taxon,
taxon_rank,
native_status,
native_status_details,
cult_status
)
SELECT
source_name,
country,
state_province,
county_parish,
family,
genus,
species,
taxon,
taxon_rank,
native_status,
'',
cult_status
FROM fwi_raw_temp
WHERE country IS NOT NULL
;

";
sql_execute_multiple($sql);	
echo $done;

?>