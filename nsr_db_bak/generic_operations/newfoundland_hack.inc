<?php

/////////////////////////////////////////////////////
// Merges separate lists for Newfoundland and 
// Labrador into one, under province name 
// "Newfoundland and Labrador"
// A compromise to deal with numerous input lists 
// that merge both regions under "Newfoundland and Labrador"
/////////////////////////////////////////////////////

echo "  Merging Newfoundland and Labrador lists...";
$sql="
DROP TABLE IF EXISTS temp_NL;
CREATE TABLE temp_NL LIKE distribution;
ALTER TABLE temp_NL DROP COLUMN distribution_id;

-- INSERT non-conflicted species
-- These have only 1 native status per source
INSERT INTO temp_NL (
source_id,
taxon_rank,
taxon,
country,
state_province,
county_parish,
native_status,
cult_status
)
SELECT DISTINCT
d.source_id,
d.taxon_rank,
d.taxon,
d.country,
'Newfoundland and Labrador',
d.county_parish,
d.native_status,
'unknown'
FROM distribution d JOIN
(
SELECT source_id, taxon, count(distinct native_status) AS statuses
FROM distribution
WHERE country='Canada' 
AND state_province IN ('Labrador','Newfoundland','Newfoundland and Labrador')
GROUP BY source_id, taxon
HAVING statuses=1
) AS a
ON d.taxon=a.taxon AND d.source_id=a.source_id
WHERE country='Canada' AND state_province IN ('Labrador','Newfoundland');

-- insert conflicted species, setting native_status=unknown
INSERT INTO temp_NL (
source_id,
taxon_rank,
taxon,
country,
state_province,
county_parish,
native_status,
cult_status
)
SELECT DISTINCT
d.source_id,
d.taxon_rank,
d.taxon,
d.country,
'Newfoundland and Labrador',
d.county_parish,
'unknown',
'unknown'
FROM distribution d JOIN
(
SELECT source_id, taxon, count(distinct native_status) AS statuses
FROM distribution
WHERE country='Canada' 
AND state_province IN ('Labrador','Newfoundland','Newfoundland and Labrador')
GROUP BY source_id, taxon
HAVING statuses>1
) AS a
ON d.taxon=a.taxon AND d.source_id=a.source_id
WHERE country='Canada' AND state_province IN ('Labrador','Newfoundland');

-- Now replace existing records
DELETE FROM distribution
WHERE country='Canada' 
AND state_province IN ('Labrador','Newfoundland','Newfoundland and Labrador');

INSERT INTO distribution (
source_id,
taxon_rank,
taxon,
country,
state_province,
county_parish,
native_status,
cult_status
)
SELECT 
source_id,
taxon_rank,
taxon,
country,
state_province,
county_parish,
native_status,
cult_status
FROM temp_NL;

DROP TABLE temp_NL;

";
sql_execute_multiple($sql);
echo $done;


?>