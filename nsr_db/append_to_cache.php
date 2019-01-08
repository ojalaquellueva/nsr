<?php

///////////////////////////////////////////////////////////
// Appends any new records from observation table to cache
///////////////////////////////////////////////////////////

echo "Appending new results to cache...";
$sql="
UPDATE observation 
SET isInCache=0
;

UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
AND o.state_province=c.state_province
AND o.county_parish=c.county_parish
SET isInCache=1
;

UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
AND o.state_province=c.state_province
SET isInCache=1
WHERE o.county_parish IS NULL AND c.county_parish IS NULL
;

UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
SET isInCache=1
WHERE o.county_parish IS NULL AND c.county_parish IS NULL
AND o.state_province IS NULL AND c.state_province IS NULL
;

INSERT INTO cache (
family,
genus,
species,
country,
state_province,
county_parish,
native_status_country,
native_status_state_province,
native_status_county_parish,
native_status,
native_status_reason,
native_status_sources,
isIntroduced,
isCultivatedNSR,
is_cultivated_taxon
)
SELECT
family,
genus,
species,
country,
state_province,
county_parish,
native_status_country,
native_status_state_province,
native_status_county_parish,
native_status,
native_status_reason,
native_status_sources,
isIntroduced,
isCultivatedNSR,
is_cultivated_taxon
FROM observation
WHERE isInCache=1
;

";
sql_execute_multiple($dbh, $sql);
echo $done;

?>