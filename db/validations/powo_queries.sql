-- -----------------------------------------------------------------
-- Checks on structure & content of raw POWO import
-- -----------------------------------------------------------------

-- -----------------------------------------------------------------
-- Parameters
-- -----------------------------------------------------------------

SET @powo_src_id:=6;

-- -----------------------------------------------------------------
-- Prepare table
-- -----------------------------------------------------------------

-- Add combined name + author column and index it
ALTER TABLE powo_raw
ADD COLUMN taxon_with_author VARCHAR(250) DEFAULT NULL
;
UPDATE powo_raw
SET taxon_with_author=CONCAT_WS(' ', `name`, `authors`)
;
ALTER TABLE powo_raw
ADD INDEX (taxon_with_author)
;

-- -----------------------------------------------------------
-- Compare counts of native species from POWO to counts
-- from other sources
-- -----------------------------------------------------------

--
-- Canada
--

SET @powo_src_id:=6;
SET @vascan_src_id:=2;

-- powo_raw vs table distribution
SELECT Canada_species_powo, Canada_species_vascan
FROM (
SELECT COUNT(DISTINCT name) AS Canada_species_powo
FROM powo_raw
WHERE taxonomicStatus='Accepted'
AND rank='species'
AND establishment='native'
AND country='Canada'
) a, 
(
SELECT COUNT(DISTINCT taxon) AS Canada_species_vascan
FROM distribution
WHERE taxon_rank='species'
AND native_status='native'
AND source_id=@vascan_src_id
AND country='Canada'
) b
;

-- Table distribution only
SELECT Canada_species_powo, Canada_species_vascan
FROM (
SELECT COUNT(DISTINCT taxon) AS Canada_species_powo
FROM distribution
WHERE taxon_rank='species'
AND native_status='native'
AND source_id=@powo_src_id
AND country='Canada'
) a, 
(
SELECT COUNT(DISTINCT taxon) AS Canada_species_vascan
FROM distribution
WHERE taxon_rank='species'
AND native_status='native'
AND source_id=@vascan_src_id
AND country='Canada'
) b
;

--
-- Alberta
--

-- Table distribution only
SELECT Alberta_species_powo, Alberta_species_vascan
FROM (
SELECT COUNT(DISTINCT taxon) AS Alberta_species_powo
FROM distribution
WHERE taxon_rank='species'
AND native_status='native'
AND source_id=@powo_src_id
AND country='Canada' AND state_province='Alberta'
) a, 
(
SELECT COUNT(DISTINCT taxon) AS Alberta_species_vascan
FROM distribution
WHERE taxon_rank='species'
AND native_status='native'
AND source_id=@vascan_src_id
AND country='Canada' AND state_province='Alberta'
) b
;

--
-- Mexico
--

SET @powo_src_id:=6;
SET @mexico_src_id:=5;

-- Table distribution only
SELECT Mexico_species_powo, Mexico_species_mexico
FROM (
SELECT COUNT(DISTINCT taxon) AS Mexico_species_powo
FROM distribution
WHERE taxon_rank='species'
AND native_status='native'
AND source_id=@powo_src_id
AND country='Mexico'
) a, 
(
SELECT COUNT(DISTINCT taxon) AS Mexico_species_mexico
FROM distribution
WHERE taxon_rank='species'
AND native_status='native'
AND source_id=@mexico_src_id
AND country='Mexico'
) b
;

--
-- USA
--

SET @powo_src_id:=6;
SET @usda_src_id:=7;

SELECT USA_species_powo, USA_species_usda
FROM (
SELECT COUNT(DISTINCT taxon) AS USA_species_powo
FROM distribution
WHERE taxon_rank='species'
AND native_status='native'
AND source_id=@powo_src_id
AND country='United States'
) a, 
(
SELECT COUNT(DISTINCT taxon) AS USA_species_usda
FROM distribution
WHERE taxon_rank='species'
AND native_status='native'
AND source_id=@usda_src_id
AND country='United States'
) b
;

--
-- Arizona
--

SELECT AZ_species_powo, AZ_species_usda
FROM (
SELECT COUNT(DISTINCT taxon) AS AZ_species_powo
FROM distribution
WHERE taxon_rank='species'
AND native_status='native'
AND source_id=@powo_src_id
AND country='United States'
AND state_province='Arizona'
) a, 
(
SELECT COUNT(DISTINCT taxon) AS AZ_species_usda
FROM distribution
WHERE taxon_rank='species'
AND native_status='native'
AND source_id=@usda_src_id
AND country='United States'
AND state_province='Arizona'
) b
;


-- -----------------------------------------------------------
-- Examine status of specific species x regions
-- -----------------------------------------------------------

SELECT taxon, country, state_province, poldiv_full, native_status, native_status_details
FROM distribution
WHERE source_id=@powo_src_id
AND country='Spain'
AND taxon LIKE 'Pinus%'
ORDER BY taxon, country, state_province, native_status
;

SELECT taxon, country, state_province, poldiv_full, native_status, native_status_details
FROM distribution
WHERE source_id=@powo_src_id
AND country='Spain'
AND taxon LIKE 'Opuntia%'
ORDER BY taxon, country, state_province, native_status
;