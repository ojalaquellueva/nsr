<?php

// Adds results fields to raw observation table

echo "Altering table observation...";
$sql="
ALTER TABLE observation
ADD COLUMN id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
ADD COLUMN native_status_country VARCHAR(25) DEFAULT NULL,
ADD COLUMN native_status_state_province VARCHAR(25) DEFAULT NULL,
ADD COLUMN native_status_county_parish VARCHAR(25) DEFAULT NULL,
ADD COLUMN native_status VARCHAR(25) DEFAULT NULL,
ADD COLUMN native_status_reason VARCHAR(250) DEFAULT NULL,
ADD COLUMN native_status_sources VARCHAR(250) DEFAULT NULL,
ADD COLUMN isIntroduced INT(1) DEFAULT NULL,
ADD COLUMN isCultivatedNSR INT(1) DEFAULT 0,
ADD COLUMN is_cultivated_taxon INT(1) DEFAULT 0,
ADD COLUMN isInCache INT(1) DEFAULT 0,
ADD PRIMARY KEY (id),
ADD INDEX (native_status_country),
ADD INDEX (native_status_state_province),
ADD INDEX (native_status_county_parish),
ADD INDEX (native_status),
ADD INDEX (native_status_reason),
ADD INDEX (native_status_sources),
ADD INDEX (isIntroduced),
ADD INDEX (isCultivatedNSR),
ADD INDEX (is_cultivated_taxon),
ADD INDEX (isInCache)
;
";
sql_execute_multiple($sql);
echo $done;

echo "Standardizing Newfoundland and Labrador as single political division...";
$sql="
-- Merge Newfoundland and Labrador
UPDATE observation
SET state_province='Newfoundland and Labrador'
WHERE country='Canada' 
AND state_province LIKE '%Newfoundland%' OR state_province LIKE '%Labrador%'
";
sql_execute_multiple($sql);
echo $done;

?>



