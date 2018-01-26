<?php

///////////////////////////////////////////////////////////
// Appends any new records from observation table to cache
///////////////////////////////////////////////////////////


if ($echo_on) echo "  Appending new results to cache...";

$sql="

-- Mark observations already in cache
UPDATE observation 
SET is_in_cache=0
;
UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
AND o.state_province=c.state_province
AND o.county_parish=c.county_parish
SET is_in_cache=1
WHERE o.county_parish IS NOT NULL AND c.county_parish IS NOT NULL
;
UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
AND o.state_province=c.state_province
SET is_in_cache=1
WHERE o.state_province IS NOT NULL AND c.state_province IS NOT NULL
AND o.county_parish IS NULL AND c.county_parish IS NULL
;
UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
SET is_in_cache=1
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
WHERE is_in_cache=0
;

UPDATE observation
SET is_in_cache=1
WHERE is_in_cache=0
;
";
sql_execute_multiple($sql);

if ($echo_on) echo "done\r\n";

?>