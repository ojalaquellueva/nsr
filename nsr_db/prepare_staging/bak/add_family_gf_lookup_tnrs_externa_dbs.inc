<?php

////////////////////////////////////////////////////////////
// Adds missing (parent) family to country list where 
// record for genus is present but family is not
// This version requires table genus_family in separate
// MySQL database gf_lookup. 
////////////////////////////////////////////////////////////

echo "    Missing families:\r\n";

echo "      Looking up using database gf_lookup...";
$sql="
UPDATE distribution_staging a 
JOIN gf_lookup.genus_family b
ON a.genus=b.genus
SET a.family=b.family
WHERE b.isAccepted=1
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "      Looking up using tnrs database...";
$sql="
-- Using tnrs, source tropicos
UPDATE distribution_staging a 
JOIN (
SELECT DISTINCT family, scientificName AS genus 
FROM tnrs4.name a join tnrs4.higherClassification b 
ON a.nameID=b.nameID 
JOIN tnrs4.synonym c ON a.nameID=c.nameID 
WHERE classificationSourceID=4 
AND nameRank='genus' 
AND family IS NOT NULL 
AND acceptance in ('Accepted')
) AS b
ON a.genus=b.genus
SET a.family=b.family
WHERE a.family IS NULL
;
-- As above, all names instead of accepted
UPDATE distribution_staging a 
JOIN (
SELECT DISTINCT family, scientificName AS genus 
FROM tnrs4.name a join tnrs4.higherClassification b 
ON a.nameID=b.nameID 
WHERE classificationSourceID=4 
AND nameRank='genus' 
AND family IS NOT NULL 
) AS b
ON a.genus=b.genus
SET a.family=b.family
WHERE a.family IS NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "      Updating family + poldiv combinations...";

// Create temporary table of missing poldiv+family combinations
$sql="
DROP TABLE IF EXISTS temp_missing_family
;
CREATE TABLE temp_missing_family
SELECT DISTINCT country, state_province, county_parish, family
FROM distribution_staging
WHERE native_status<>'introduced' AND taxon_rank<>'hybrid'
;
ALTER TABLE temp_missing_family
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish),
ADD INDEX (family)
;

-- Mark family+poldiv combinations already present
UPDATE temp_missing_family f JOIN distribution_staging d
ON f.family=d.taxon AND f.country=d.country AND f.state_province=d.state_province
AND f.county_parish=d.county_parish
SET f.family='DELETE'
;

-- Delete marked records
DELETE FROM temp_missing_family
WHERE family='DELETE' OR family IS NULL OR TRIM(family)=''
;
";
sql_execute_multiple($dbh, $sql);

// Insert missing families
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
family
)
SELECT
'$src',
country,
state_province,
county_parish,
family,
'family',
'native',
'unknown',
family
FROM temp_missing_family
;
";
sql_execute_multiple($dbh, $sql);

// Drop temporary table
$sql="
DROP TABLE temp_missing_family;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>