<?php

echo "  Loading metadata on comprehensive checklists:\r\n";

echo "    country...";
$sql="
-- countries
INSERT INTO cclist (
country,
state_province,
county_parish
) 
SELECT
b.country,
'',
''
FROM poldiv_source_staging a JOIN country b
ON a.poldiv_id=b.country_id
LEFT JOIN 
(
SELECT DISTINCT country
FROM cclist 
WHERE state_province=''
AND county_parish=''
) AS c
ON b.country=c.country
WHERE c.country IS NULL
;
";
sql_execute_multiple($sql);
echo $done;

echo "    state_province...";
$sql="
-- state_province
INSERT INTO cclist (
country,
state_province,
county_parish
) 
SELECT
b.country,
b.state_province_std,
''
FROM poldiv_source_staging a JOIN state_province b
ON a.poldiv_id=b.state_province_id
LEFT JOIN 
(
SELECT DISTINCT b.state_province_id
FROM cclist a JOIN state_province b
ON a.country=b.country
AND a.state_province=b.state_province_std
WHERE county_parish=''
) AS c
ON b.state_province_id=c.state_province_id
WHERE c.state_province_id IS NULL
;
";
sql_execute_multiple($sql);
echo $done;

// county_parish not ready!!!

?>
