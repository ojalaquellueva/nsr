<?php

/////////////////////////////////////
// Populates missing family and genus
// in observations table
/////////////////////////////////////

include "dbw_open.php";

// "species" is family name
$sql="
UPDATE observation 
SET family=species
WHERE $JOB_WHERE_NA
AND (family IS NULL OR TRIM(family=''))
AND species LIKE '%aceae'
;

";
sql_execute_multiple($dbh, $sql);

// "species" not a family name
$sql="
UPDATE observation 
SET genus=strSplit(species,' ',1)
WHERE $JOB_WHERE_NA 
AND (genus IS NULL OR TRIM(genus=''))
AND species NOT LIKE '%aceae'
;
";
sql_execute_multiple($dbh, $sql);

// Populate family if missing and genus has only
// one family
$sql="
UPDATE observation o JOIN gf_lookup b
ON o.genus=b.genus
SET o.family=b.family
WHERE $JOB_WHERE 
AND (family IS NULL OR TRIM(family=''))
AND (genus IS NOT NULL AND TRIM(genus<>''))
AND b.fams=1
;
";
sql_execute_multiple($dbh, $sql);


include "db_close.php";

?>