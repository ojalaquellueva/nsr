<?php

///////////////////////////////////////////////////////////////
// Removes from cache any species+poldiv combinations
// in observation table. This script is run if $replace_cache
// option set to true (command line option -r=true)
///////////////////////////////////////////////////////////////

include "dbw_open.php";

$sql="
UPDATE observation 
SET is_in_cache=0
;

UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
AND o.state_province=c.state_province
AND o.county_parish=c.county_parish
SET c.native_status_reason='remove'
;

UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
AND o.state_province=c.state_province
SET c.native_status_reason='remove'
WHERE o.county_parish IS NULL AND c.county_parish IS NULL
;

UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
SET c.native_status_reason='remove'
WHERE o.county_parish IS NULL AND c.county_parish IS NULL
AND o.state_province IS NULL AND c.state_province IS NULL
;

-- Delete records from cache
DELETE FROM cache
WHERE native_status_reason='remove'
;
";
sql_execute_multiple($sql);

include "db_close.php";

?>