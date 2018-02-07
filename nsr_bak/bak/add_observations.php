<?php

include "dbw_open.php";

$sql_insert_obs="
INSERT INTO observation (
family,
genus,
species,
country,
state_province,
county_parish
)
VALUES (
'$fam',
'$genus',
'$species',
'$country',
'$stateprovince',
'$countyparish'
);	

";
sql_execute_multiple($sql_insert_obs);
//	echo "<br />$sql<br />";

$sql="
ALTER TABLE observation
ADD INDEX (family),
ADD INDEX (genus),
ADD INDEX (species),
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish),
ADD INDEX (is_in_cache)
;

UPDATE observation 
SET state_province=NULL
WHERE state_province='';

UPDATE observation 
SET county_parish=NULL
WHERE county_parish='';

";
sql_execute_multiple($sql);

include "db_close.php";

?>