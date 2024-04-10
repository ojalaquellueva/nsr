-- For testing only

SET @powo_src_id:=6;

SELECT COUNT(*) FROM distribution
WHERE source_id=@powo_src_id 
AND state_province IS NOT NULL AND state_province<>''
; 

-- 
-- Clear previous state-level records
-- 

DELETE FROM distribution
WHERE source_id=@powo_src_id 
AND state_province IS NOT NULL AND state_province<>''
; 

-- 
-- Add state-level records
-- 

-- species
INSERT INTO distribution (
source_id,
country,
state_province,
taxon,
taxon_rank,
native_status,
cult_status
)
SELECT 
6,
country,
state_province,
name,
`rank`,
establishment,
NULL
FROM powo_raw
WHERE is_dupe=0
AND country IS NOT NULL
AND state_province IS NOT NULL
;

-- genus
INSERT INTO distribution (
source_id,
country,
state_province,
taxon,
taxon_rank,
native_status,
cult_status
)
SELECT DISTINCT
6,
country,
state_province,
strSplit(name,' ',1),
'genus',
'present',
NULL
FROM powo_raw
WHERE is_dupe=0
AND country IS NOT NULL
AND state_province IS NOT NULL
;

-- family
INSERT INTO distribution (
source_id,
country,
state_province,
taxon,
taxon_rank,
native_status,
cult_status
)
SELECT DISTINCT
6,
country,
state_province,
family,
'family',
'present',
NULL
FROM powo_raw
WHERE is_dupe=0
AND country IS NOT NULL
AND state_province IS NOT NULL
AND family IS NOT NULL
;

-- 
-- Populate concatenated political division columns
-- 

-- Populating column state_province_full
UPDATE distribution
SET state_province_full=CONCAT_WS(':',
country,state_province
)
WHERE country IS NOT NULL AND state_province IS NOT NULL
;

-- Populating column county_parish_full
UPDATE distribution
SET county_parish_full=CONCAT_WS(':',
country,state_province,county_parish
)
WHERE country IS NOT NULL 
AND state_province IS NOT NULL
AND county_parish IS NOT NULL
;

-- Populating column poldiv_full
UPDATE distribution
SET poldiv_full=
CASE
WHEN country IS NOT NULL AND state_province IS NULL THEN country
WHEN state_province IS NOT NULL AND county_parish IS NULL THEN state_province_full
WHEN county_parish IS NOT NULL THEN county_parish_full
ELSE NULL
END
;

-- Populating column poldiv_type
UPDATE distribution
SET poldiv_type=
CASE
WHEN country IS NOT NULL AND state_province IS NULL THEN 'country'
WHEN state_province IS NOT NULL AND county_parish IS NULL THEN 'state_province'
WHEN county_parish IS NOT NULL THEN 'county_parish'
ELSE NULL
END
;

--
-- Mark duplicate records
--

ALTER TABLE distribution
ADD COLUMN is_dupe INT(1) DEFAULT NULL
;
UPDATE distribution
SET is_dupe=1
WHERE country IS NOT NULL
;

UPDATE distribution r JOIN
(
SELECT 
poldiv_full,
taxon, 
(
SELECT distribution_id
FROM distribution r
WHERE distribution.taxon=r.taxon AND distribution.poldiv_full=r.poldiv_full
AND distribution.source_id=@powo_src_id  
AND r.source_id=@powo_src_id  
ORDER BY distribution_id
LIMIT 1
) AS first_id
FROM distribution
WHERE source_id=@powo_src_id  
GROUP BY poldiv_full, taxon
) AS nodupes
ON r.distribution_id=nodupes.first_id
SET is_dupe=0
;

-- Check results
SELECT source_id, is_dupe, COUNT(*)
FROM FROM distribution
GROUP BY source_id, is_dupe
ORDER BY source_id, is_dupe
;

-- CAREFUL! Check before running
DELETE FROM distribution
WHERE is_dupe=1
AND source_id=@powo_src_id
;

ALTER TABLE distribution
DROP COLUMN is_dupe
;