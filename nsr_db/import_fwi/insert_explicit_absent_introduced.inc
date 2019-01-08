<?php

/////////////////////////////////////////////////////
// Inserts explicit country x species combinations
// where species marked as absent or introduced
// These can safely propagate downward from regions
// to countries in regions.
/////////////////////////////////////////////////////

echo "Inserting explicit introduced/absent by region...";

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
SELECT DISTINCT
'$src',
b.country,
NULL,
NULL,
family,
genus,
species,
taxon,
taxon_rank,
native_status,
CONCAT('Status inferred from containing region ', a.region),
cult_status
FROM fwi_raw_temp a JOIN fwi_region_country b
ON a.region=b.region
WHERE a.country IS NULL
AND b.country NOT IN ($cclist_countries)
AND a.native_status IN ('absent','introduced')
;
";
sql_execute_multiple($dbh, $sql);	
echo $done;

?>