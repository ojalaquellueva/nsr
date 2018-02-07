<?php

include "dbw_open.php";

$sql="
UPDATE observation 
SET is_in_cache=0
WHERE $BATCH_WHERE_NA 
;

UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
AND o.state_province=c.state_province
AND o.county_parish=c.county_parish
SET is_in_cache=1
WHERE $BATCH_WHERE 
;

UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
AND o.state_province=c.state_province
SET is_in_cache=1
WHERE $BATCH_WHERE 
AND o.county_parish IS NULL AND c.county_parish IS NULL
;

UPDATE observation o JOIN cache c
ON o.species=c.species
AND o.country=c.country
SET is_in_cache=1
WHERE $BATCH_WHERE 
AND o.county_parish IS NULL AND c.county_parish IS NULL
AND o.state_province IS NULL AND c.state_province IS NULL
;
";
sql_execute_multiple($sql);

include "db_close.php";

?>