-- ------------------------------------------------------------------------
-- Fix false state endemics in Mexico list in production database
-- 2019-05-29
-- Updates 2024-09-08: 
--   * Correction added to pipeline (the right way)
--   * This bugfix was incorrectly implement in this hotfix!
-- -------------------------------------------------------------------------

set @srcid:=5;   -- source_id for source "mexico"

-- List species in Mexico which are listed as state endemics but not country endemics
SELECT DISTINCT state_end.taxon, state_end.country, state_end.state_province, ctry_end.taxon, ctry_end.country, ctry_end.state_province 
FROM 
(
SELECT DISTINCT taxon, country, state_province FROM distribution where source_id=@srcid AND native_status='endemic' AND state_province IS NOT NULL
) AS state_end
LEFT JOIN 
(
SELECT DISTINCT taxon, country, state_province FROM distribution where source_id=@srcid AND native_status='endemic' AND state_province IS NULL
) AS ctry_end
ON state_end.taxon=ctry_end.taxon
WHERE ctry_end.taxon IS NULL
ORDER BY state_end.taxon, state_end.country, state_end.state_province
;

-- 
-- Update native_status for these species
-- 

-- Backup
CREATE TABLE distribution_bak LIKE distribution;
INSERT INTO distribution_bak SELECT * FROM distribution;

-- Add temporary new status column
ALTER TABLE distribution 
ADD COLUMN native_status_new VARCHAR(100) DEFAULT NULL,
ADD COLUMN native_status_bak VARCHAR(100) DEFAULT NULL
;

-- Backup the old column
UPDATE distribution
SET native_status_bak=native_status
;

-- Update the new column
UPDATE distribution a JOIN 
(
SELECT DISTINCT state_end.taxon, state_end.country, state_end.state_province
FROM 
(
SELECT DISTINCT taxon, country, state_province FROM distribution where source_id=@srcid AND native_status='endemic' AND state_province IS NOT NULL
) AS state_end
LEFT JOIN 
(
SELECT DISTINCT taxon, country, state_province FROM distribution where source_id=@srcid AND native_status='endemic' AND state_province IS NULL
) AS ctry_end
ON state_end.taxon=ctry_end.taxon
WHERE ctry_end.taxon IS NULL
) AS b
ON a.taxon=b.taxon AND a.country=b.country AND a.state_province=b.state_province
SET a.native_status_new='native'
WHERE a.source_id=@srcid
;

-- Index it
ALTER TABLE distribution
ADD INDEX (native_status_new);

-- Inspect before updating
SELECT source_id, taxon, country, state_province, native_status, native_status_new 
FROM distribution
WHERE source_id=@srcid AND native_status='endemic'
ORDER BY taxon, country, state_province 
;

-- compare to:
SELECT source_id, taxon, country, state_province, native_status, native_status_new 
FROM distribution
WHERE native_status_new IS NOT NULL
ORDER BY taxon, country, state_province 
;

-- Make the final update
UPDATE distribution
SET native_status=native_status_new
WHERE native_status_new IS NOT NULL
;

-- Remove temporary column
ALTER TABLE distribution
DROP native_status_new, DROP native_status_bak
;

