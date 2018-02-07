<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
//
///////////////////////////////////////////////////////

echo "Loading raw data to staging table distribution_staging:\r\n";


// The following works because no species has >1 native status, even if
// it occurs in >1 state
echo "  Inserting country occurrences...";
$sql="
INSERT INTO distribution_staging (
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
cult_status
)
SELECT DISTINCT
'$src',
'Brazil',
NULL,
NULL,
family,
genus,
species,
taxon,
taxon_rank,
native_status,
cult_status
FROM `$tbl_raw`
ORDER BY family, taxon
;
";
sql_execute_multiple($sql);
echo $done;

echo "  Inserting state occurrences...";
$sql="
INSERT INTO distribution_staging (
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
cult_status
)
SELECT DISTINCT
'$src',
'Brazil',
state_province,
NULL,
family,
genus,
species,
taxon,
taxon_rank,
native_status,
cult_status
FROM `$tbl_raw`
WHERE state_province IS NOT NULL
ORDER BY state_province, family, taxon
;
";
sql_execute_multiple($sql);
echo $done;

?>