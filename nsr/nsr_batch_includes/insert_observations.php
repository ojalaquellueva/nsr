<?php

if ($echo_on) echo "Inserting observations...";

// insert the raw records
$sql="
INSERT INTO observation (
family,
genus,
species,
country,
state_province,
county_parish,
user_id
)
SELECT 
family,
genus,
species,
country,
state_province,
county_parish,
user_id
FROM observation_raw
;

-- HACK
-- Merge Newfoundland and Labrador
UPDATE observation
SET state_province='Newfoundland and Labrador'
WHERE country='Canada' 
AND state_province LIKE '%Newfoundland%' OR state_province LIKE '%Labrador%'

";
sql_execute_multiple($sql);

// Convert empty strings to null
$sql="
UPDATE observation 
SET state_province=NULL
WHERE state_province=''
;
UPDATE observation 
SET county_parish=NULL
WHERE county_parish=''
;
";
sql_execute_multiple($sql);

// Populate the optimization columns
$sql="
UPDATE observation
SET state_province_full=CONCAT_WS(':',
country,state_province
)
WHERE country IS NOT NULL AND state_province IS NOT NULL
;
UPDATE observation
SET county_parish_full=CONCAT_WS(':',
country,state_province,county_parish
)
WHERE country IS NOT NULL 
AND state_province IS NOT NULL
AND county_parish IS NOT NULL
;
UPDATE observation
SET poldiv_full=
CASE
WHEN country IS NOT NULL AND state_province IS NULL THEN country
WHEN state_province IS NOT NULL AND county_parish IS NULL THEN state_province_full
WHEN county_parish IS NOT NULL THEN county_parish_full
ELSE NULL
END
;
UPDATE observation
SET poldiv_type=
CASE
WHEN country IS NOT NULL AND state_province IS NULL THEN 'country'
WHEN state_province IS NOT NULL AND county_parish IS NULL THEN 'state_province'
WHEN county_parish IS NOT NULL THEN 'county_parish'
ELSE NULL
END
;
";
sql_execute_multiple($sql);



// Index observation
$sql="
ALTER TABLE observation
ADD INDEX (family),
ADD INDEX (genus),
ADD INDEX (species),
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish),
ADD INDEX (is_in_cache),
ADD INDEX (state_province_full),
ADD INDEX (county_parish_full),
ADD INDEX (poldiv_full),
ADD INDEX (poldiv_type)
;
";
sql_execute_multiple($sql);

// Drop the raw table
$sql="
-- DROP TABLE IF EXISTS observation_raw;
";
sql_execute_multiple($sql);

if ($echo_on) echo "done\r\n";

?>