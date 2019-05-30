<?php

echo "  Loading metadata on comprehensive checklists...";

// country
$sql="
INSERT INTO cclist (
country
)
SELECT DISTINCT
country
FROM poldiv_source_staging a JOIN country b
ON a.poldiv_id=b.country_id
WHERE a.poldiv_type='country'
AND a.checklist_type='comprehensive'
;
";
sql_execute_multiple($dbh, $sql);	

// state_province
$sql="
INSERT INTO cclist (
country, state_province
)
SELECT DISTINCT
country, state_province
FROM poldiv_source_staging a JOIN state_province b
ON a.poldiv_id=b.state_province_id
WHERE a.poldiv_type='state_province'
AND a.checklist_type='comprehensive'
;
";
sql_execute_multiple($dbh, $sql);	

/* Not yet supported
// county/parish
$sql="
INSERT INTO cclist (
country, state_province, county_parish
)
SELECT DISTINCT
country, state_province, county_parish
FROM poldiv_source_staging a JOIN , county_parish b
ON a.poldiv_id=b., county_parish_id
WHERE a.poldiv_type=', county_parish'
AND a.checklist_type='comprehensive'
;
";
sql_execute_multiple($dbh, $sql);
*/	

$sql="
DROP TABLE IF EXISTS cclist_temp;
CREATE TABLE cclist_temp LIKE cclist;
INSERT INTO cclist_temp SELECT DISTINCT * FROM cclist;
DROP TABLE cclist;
RENAME TABLE cclist_temp TO cclist;
";
sql_execute_multiple($dbh, $sql);	
//echo $done;

// Setting empty strings to null for state and county
// Essential for absence flagging to work
$sql="
UPDATE cclist
SET state_province=NULL
WHERE trim(state_province)=''
;
UPDATE cclist
SET county_parish=NULL
WHERE trim(county_parish)=''
;
";
sql_execute_multiple($dbh, $sql);	
echo $done;


?>
