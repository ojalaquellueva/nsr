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
sql_execute_multiple($sql);
echo $done;
?>
