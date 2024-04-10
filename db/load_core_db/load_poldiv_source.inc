<?php

echo "  Loading metadata on checklist regions...";
$sql="
INSERT INTO poldiv_source (
poldiv_id,
poldiv_type,
source_id,
checklist_type,
checklist_details
) 
SELECT
poldiv_id,
poldiv_type,
$source_id,
checklist_type,
checklist_details
FROM poldiv_source_staging
;
UPDATE poldiv_source a JOIN country b
ON a.poldiv_id=b.country_id
SET a.poldiv_name=b.country
WHERE a.poldiv_type='country'
;
UPDATE poldiv_source a JOIN state_province b
ON a.poldiv_id=b.state_province_id
SET a.poldiv_name=b.state_province_std
WHERE a.poldiv_type='state_province'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Removing redundant records from table poldiv_source...";
$sql="
DROP TABLE IF EXISTS poldiv_source_uniq;
CREATE TABLE poldiv_source_uniq LIKE poldiv_source;
INSERT INTO poldiv_source_uniq (
poldiv_id,
poldiv_name,
poldiv_type,
source_id,
checklist_type,
checklist_details
)
SELECT DISTINCT 
poldiv_id,
poldiv_name,
poldiv_type,
source_id,
checklist_type,
checklist_details
FROM poldiv_source;
DROP TABLE poldiv_source;
RENAME TABLE poldiv_source_uniq TO poldiv_source;
";
sql_execute_multiple($dbh, $sql);
echo $done;


?>