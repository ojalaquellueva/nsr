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

/*
echo "  Marking duplicate records...";
// this step only necessary if source came with its own ID field
// If artificial PK was added in alter_tbl_raw.inc then this 
// step won't do anything. But comment out if you don't need
// it--it's slow.
$sql="
UPDATE `$tbl_raw`
SET include=0;
UPDATE `$tbl_raw` r JOIN
(
SELECT 
country,
taxon, 
(
SELECT id
FROM `$tbl_raw` r
WHERE `$tbl_raw`.taxon=r.taxon AND `$tbl_raw`.country=r.country
ORDER BY id
LIMIT 1
) AS first_id
FROM `$tbl_raw`
GROUP BY country, taxon
) AS nodupes
ON r.id=nodupes.first_id
SET include=1
;
";
sql_execute_multiple($dbh, $sql);
echo $done;
*/

echo "  Inserting unique records...";
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
SELECT DISTINCT
'$src',
country,
state_province,
county_parish,
taxon,
taxon_rank,
native_status,
cult_status
FROM `$tbl_raw`
WHERE include=1
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>