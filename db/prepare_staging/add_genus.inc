<?php

////////////////////////////////////////////////////////////
// Adds missing (parent) genus to country list where record for 
// species is present but genus is not
////////////////////////////////////////////////////////////

echo "    Missing genera...";

// Populate genus column...";
$sql="
UPDATE distribution_staging
SET genus=TRIM(strSplit(taxon,' ',1))
;
";
sql_execute_multiple($dbh, $sql);

// Create temporary table of missing country+genus combinations
$sql="
DROP TABLE IF EXISTS temp_missing_genus
;
CREATE TABLE temp_missing_genus
SELECT DISTINCT country, state_province, county_parish, genus
FROM distribution_staging
WHERE native_status IN ('native','endemic') AND taxon_rank<>'hybrid'
;

ALTER TABLE temp_missing_genus
ADD column del VARCHAR(15) default null
;

ALTER TABLE temp_missing_genus
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish),
ADD INDEX (genus)
;

-- Mark genus+poldiv combinations already present
UPDATE temp_missing_genus g JOIN distribution_staging d
ON g.genus=d.taxon AND g.country=d.country AND g.state_province=d.state_province
AND g.county_parish=d.county_parish
SET g.del='DELETE'
;

ALTER TABLE temp_missing_genus
ADD INDEX (del)
;

-- Delete marked records
DELETE FROM temp_missing_genus
WHERE del='DELETE' OR genus IS NULL OR TRIM(genus)=''
;
";
sql_execute_multiple($dbh, $sql);

// Insert missing genera...";
$sql="
INSERT INTO distribution_staging (
source_name,
country,
state_province,
county_parish,
taxon,
taxon_rank,
native_status,
cult_status,
genus
)
SELECT
'$src',
country,
state_province,
county_parish,
genus,
'genus',
'native',
'unknown',
genus
FROM temp_missing_genus
;
";
sql_execute_multiple($dbh, $sql);

// Drop temporary table
$sql="
DROP TABLE temp_missing_genus;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>