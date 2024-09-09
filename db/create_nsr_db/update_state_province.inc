<?php

echo "Preparing state_province:\n";

// Add GADM fields
echo "  Altering state_province...";
$sql="
ALTER TABLE state_province
ADD COLUMN country_iso_alpha3 VARCHAR(3) DEFAULT NULL,
ADD COLUMN gid_0 VARCHAR(3) DEFAULT NULL,
ADD COLUMN gid_1 VARCHAR(12) DEFAULT NULL,
ADD INDEX (country_iso_alpha3),
ADD INDEX (gid_0),
ADD INDEX (gid_1)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

// Populate country iso3 field
echo "  Populating country iso3 fields...";
$sql="
UPDATE state_province a JOIN country b
ON a.country_iso=b.country_iso
SET a.country_iso_alpha3=b.country_iso_alpha3,
a.gid_0=b.country_iso_alpha3
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

// Populate GADM fields
echo "Populating GADM id fields...";
$sql="
UPDATE state_province a JOIN gadm_admin_1_raw b
ON a.gid_0=b.gid_0 
AND a.state_province=b.name_1
SET a.gid_1=b.gid_1
;
-- Alternate joins
UPDATE state_province a JOIN gadm_admin_1_raw b
ON a.gid_0=b.gid_0 
AND a.state_province_ascii=b.name_1
SET a.gid_1=b.gid_1
WHERE a.gid_1 IS NULL
;
UPDATE state_province a JOIN gadm_admin_1_raw b
ON a.gid_0=b.gid_0 
AND a.state_province_std=b.name_1
SET a.gid_1=b.gid_1
WHERE a.gid_1 IS NULL
;
-- Alternate joins via table state_province_name
UPDATE state_province a JOIN state_province_name a2
ON a.state_province_id=a2.state_province_id
JOIN gadm_admin_1_raw b
ON a.gid_0=b.gid_0 
AND a2.state_province_name=b.name_1
SET a.gid_1=b.gid_1
WHERE a.gid_1 IS NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>