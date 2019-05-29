<?php

/////////////////////////////////////
// Populates missing family and genus
// in observations table
/////////////////////////////////////

//include "dbw_open.php";

// "species" is family name
$sql="
UPDATE observation 
SET family=species
WHERE (family IS NULL OR TRIM(family=''))
AND species LIKE '%aceae'
;
";
sql_execute_multiple($dbh, $sql);

// Family but no species
// Copy family to species column
$sql="
UPDATE observation 
SET species=family
WHERE (family IS NOT NULL AND TRIM(family=''))
AND (species IS NULL OR TRIM(species=''))
;
";
sql_execute_multiple($dbh, $sql);


// "species" not a family name
$sql="
UPDATE observation 
SET genus=strSplit(species,' ',1)
WHERE (genus IS NULL OR TRIM(genus=''))
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
WHERE (o.family IS NULL OR TRIM(o.family=''))
AND (o.genus IS NOT NULL AND TRIM(o.genus<>''))
AND b.fams=1
;
";
sql_execute_multiple($dbh, $sql);


//include "db_close.php";

?>