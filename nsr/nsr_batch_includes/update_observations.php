<?php

include "dbw_open.php";

if ($echo_on)  echo "Updating observations from cache...";
// Transfer results from cache to observation table
$sql="
-- country only results
UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
SET 
o.state_province=c.state_province,
o.county_parish=c.county_parish,
o.native_status_country=c.native_status_country,
o.native_status_state_province=c.native_status_state_province,
o.native_status_county_parish=c.native_status_county_parish,
o.native_status=c.native_status,
o.native_status_reason=c.native_status_reason,
o.native_status_sources=c.native_status_sources,
o.isIntroduced=c.isIntroduced,
o.isCultivatedNSR=c.isCultivatedNSR,
o.is_cultivated_taxon=c.is_cultivated_taxon
WHERE
o.state_province IS NULL AND c.state_province IS NULL
AND o.county_parish IS NULL AND c.county_parish IS NULL
;

-- state-level results
UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
AND o.state_province=c.state_province 
SET 
o.state_province=c.state_province,
o.county_parish=c.county_parish,
o.native_status_country=c.native_status_country,
o.native_status_state_province=c.native_status_state_province,
o.native_status_county_parish=c.native_status_county_parish,
o.native_status=c.native_status,
o.native_status_reason=c.native_status_reason,
o.native_status_sources=c.native_status_sources,
o.isIntroduced=c.isIntroduced,
o.isCultivatedNSR=c.isCultivatedNSR,
o.is_cultivated_taxon=c.is_cultivated_taxon
WHERE
o.county_parish IS NULL AND c.county_parish IS NULL
;

-- county-level results
UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
AND o.state_province=c.state_province 
AND o.county_parish=c.county_parish
SET 
o.state_province=c.state_province,
o.county_parish=c.county_parish,
o.native_status_country=c.native_status_country,
o.native_status_state_province=c.native_status_state_province,
o.native_status_county_parish=c.native_status_county_parish,
o.native_status=c.native_status,
o.native_status_reason=c.native_status_reason,
o.native_status_sources=c.native_status_sources,
o.isIntroduced=c.isIntroduced,
o.isCultivatedNSR=c.isCultivatedNSR,
o.is_cultivated_taxon=c.is_cultivated_taxon
;
";
sql_execute_multiple($sql);
if ($echo_on)  echo $done;

include "db_close.php";
?>