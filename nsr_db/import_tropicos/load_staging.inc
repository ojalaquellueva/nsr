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

echo "  Marking duplicate records...";
$sql="
ALTER TABLE tropicos_raw
ADD COLUMN include INT(1) DEFAULT 0,
ADD INDEX (include)
;
UPDATE tropicos_raw r JOIN
(
SELECT 
country,
taxon, 
(
SELECT id
FROM tropicos_raw r
WHERE tropicos_raw.taxon=r.taxon AND tropicos_raw.country=r.country
ORDER BY id
LIMIT 1
) AS first_id
FROM tropicos_raw
GROUP BY country, taxon
) AS nodupes
ON r.id=nodupes.first_id
SET include=1
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Inserting unique records...";
$sql="
INSERT INTO distribution_staging (
source_name,
country,
taxon,
taxon_rank,
native_status,
cult_status
)
SELECT
'$src',
country,
taxon,
taxon_rank,
native_status,
cult_status
FROM tropicos_raw
WHERE include=1
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>