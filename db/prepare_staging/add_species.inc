<?php

////////////////////////////////////////////////////////////
// Adds missing (parent) species to country list where record for 
// infraspecific taxon (variety, subspecies, etc.) is present but 
// species is not
////////////////////////////////////////////////////////////

echo "    Missing species...";

// Populate species column
$sql="
UPDATE distribution_staging
SET species=CONCAT_WS(' ',
strSplit(taxon,' ',1),
strSplit(taxon,' ',2)
)
;
";
sql_execute_multiple($dbh, $sql);

// Create temporary table of missing country+species combinations
$sql="
DROP TABLE IF EXISTS temp_missing_species
;
-- Only need to extract species if taxon is infraspecific
CREATE TABLE temp_missing_species
SELECT DISTINCT country, state_province, county_parish, species
FROM distribution_staging
WHERE native_status IN ('native','endemic') AND taxon_rank<>'hybrid'
AND taxon LIKE '% % %';
;

ALTER TABLE temp_missing_species
ADD COLUMN del VARCHAR(15) DEFAULT NULL
;

ALTER TABLE temp_missing_species
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish),
ADD INDEX (species)
;

-- Mark species+poldiv combinations already present
UPDATE temp_missing_species s JOIN (
SELECT DISTINCT taxon, country, state_province, county_parish
FROM distribution_staging 
WHERE taxon LIKE '% % %'
) d
ON s.species=d.taxon 
AND s.country=d.country 
AND s.state_province=d.state_province
AND s.county_parish=d.county_parish
SET s.del='DELETE'
;

ALTER TABLE temp_missing_species
ADD INDEX (del)
;

-- Delete marked records
DELETE FROM temp_missing_species
WHERE del='DELETE'
;
";
sql_execute_multiple($dbh, $sql);

// Insert missing species
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
'native',
'unknown',
species
FROM temp_missing_species
;
";
sql_execute_multiple($dbh, $sql);

// Drop temporary table
$sql="
DROP TABLE temp_missing_species;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>