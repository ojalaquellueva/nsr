<?php

include "dbw_open.php";

$sql_insert_obs="
TRUNCATE observation;
INSERT INTO observation (
job,
batch,
family,
genus,
species,
country,
state_province,
county_parish
)
VALUES (
'$job',
1,
'$fam',
'$genus',
'$species',
'$country',
'$stateprovince',
'$countyparish'
);	

";
sql_execute_multiple($dbh, $sql_insert_obs);
//	echo "<br />$sql<br />";

$sql="
UPDATE observation 
SET state_province=NULL
WHERE state_province='';

UPDATE observation 
SET county_parish=NULL
WHERE county_parish='';

";
sql_execute_multiple($dbh, $sql);

include "db_close.php";

?>