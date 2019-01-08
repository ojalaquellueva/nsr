<?php

////////////////////////////////////////////////////////////
// Adds missing (parent) species to country list where record for 
// infraspecific taxon (variety, subspecies, etc.) is present but 
// species is not
////////////////////////////////////////////////////////////

echo "  Adding missing parent species...";

//echo "  Populating species column...";
$sql="
UPDATE distribution_staging
SET species=CONCAT_WS(' ',
strSplit(taxon,' ',1),
strSplit(taxon,' ',2)
)
;
";
sql_execute_multiple($dbh, $sql);
//echo $done;

//echo "  Creating temporary table of missing country+species...";
$sql="
DROP TABLE IF EXISTS temp_missing_species
;
CREATE TABLE temp_missing_species
SELECT DISTINCT country, state_province, county_parish, species
FROM distribution_staging
WHERE native_status<>'introduced' AND taxon_rank<>'hybrid'
;
-- Remove species+poldiv combinations already present
-- Mark, then delete
-- countyParish records
UPDATE temp_missing_species s JOIN distribution_staging d
ON s.species=d.taxon AND s.country=d.country AND s.state_province=d.state_province
AND s.county_parish=d.county_parish
SET s.species='DELETE'
;
-- stateProvince records
UPDATE temp_missing_species s JOIN distribution_staging d
ON s.species=d.taxon AND s.country=d.country AND s.state_province=d.state_province
SET s.species='DELETE'
WHERE s.county_parish IS NULL AND d.county_parish IS NULL
;
-- country records
UPDATE temp_missing_species s JOIN distribution_staging d
ON s.species=d.taxon AND s.country=d.country
SET s.species='DELETE'
WHERE s.state_province IS NULL AND d.state_province IS NULL
;
DELETE FROM temp_missing_species
WHERE species='DELETE'
;
";
sql_execute_multiple($dbh, $sql);


//echo "  Inserting missing species...";
// then delete temporary table
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
species
)
SELECT
'$src',
country,
state_province,
county_parish,
species,
'species',
'unknown',
'unknown',
species
FROM temp_missing_species
;
";
sql_execute_multiple($dbh, $sql);
//echo $done;

//echo "  Dropping temporary table...";
$sql="
DROP TABLE temp_missing_species;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>