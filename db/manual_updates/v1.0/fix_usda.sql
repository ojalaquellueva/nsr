-- -------------------------------------------------------------------
-- Set erroneous values of "unknown" to "native for usda source only
-- This is temporary hack in existing database
-- Permanent fix will be applied next time database is rebuilt
-- -------------------------------------------------------------------

set @srcid:=9;   -- source_id for "usda"; adjust accordingly

-- back up existing values
DROP TABLE IF EXISTS distribution_usda_native_status_bak;
CREATE TABLE distribution_usda_native_status_bak
SELECT distribution_id, source_id, taxon, state_province, native_status
FROM distribution
WHERE source_id=@srcid
;

-- To restore:
-- update distribution a
-- join distribution_usda_native_status_bak b
-- on a.distribution_id=b.distribution_id
-- set a.native_status=b.native_status
-- where a.source_id=@srcid
-- ;

-- 
-- Fix distribution table
--

-- Subspecific taxa & species
UPDATE distribution
SET native_status='native'
WHERE source_id=@srcid
AND taxon_rank IN ('fo.','subsp.','var.','species')
AND native_status='unknown'
;

-- Temporarily add genus column
ALTER TABLE distribution
ADD COLUMN genus VARCHAR(100) DEFAULT NULL
;
UPDATE distribution
SET genus=strSplit(taxon,' ',1)
WHERE taxon_rank NOT IN ('hybrid','family')
AND source_id=@srcid
;
ALTER TABLE distribution
ADD INDEX (genus);

-- Genus: mark native if >=1 native species or subspecific taxon
UPDATE distribution a JOIN (
SELECT DISTINCT genus 
FROM distribution
WHERE source_id=@srcid
AND taxon_rank IN ('fo.','subsp.','var.','species')
AND native_status='native'
) b
ON a.genus=b.genus
SET a.native_status='native'
WHERE a.source_id=@srcid
AND a.taxon_rank='genus' 
AND a.native_status='unknown'
; 

-- Mark changed records
ALTER TABLE distribution
ADD COLUMN changed INT(1) DEFAULT 0
;
UPDATE distribution a JOIN distribution_usda_native_status_bak b
ON a.distribution_id=b.distribution_id
SET a.changed=1
WHERE a.native_status<>b.native_status
AND a.source_id=@srcid
;
ALTER TABLE distribution ADD INDEX (changed);

-- 
-- Empty the cache of any USDA species which have been changed
-- 

-- Column for marking records to delete
-- Bit safer, can inspect before final delete
ALTER TABLE cache ADD COLUMN del INT(1) DEFAULT NULL;

-- populate poldivfull in cache
-- not sure why this wasn't done before
UPDATE cache
SET poldiv_full=country
WHERE country IS NOT NULL 
AND state_province IS NULL
AND county_parish IS NULL
;
UPDATE cache
SET poldiv_full=CONCAT_WS(':',country,state_province)
WHERE country IS NOT NULL 
AND state_province IS NOT NULL
AND county_parish IS NULL
;
UPDATE cache
SET poldiv_full=CONCAT_WS(':',country,state_province,county_parish)
WHERE country IS NOT NULL 
AND state_province IS NOT NULL
AND county_parish IS NOT NULL
;

-- Mark cache records to delete
-- UPDATE cache a JOIN distribution b
-- ON a.species=b.taxon 
-- AND a.poldiv_full=b.poldiv_full
-- SET del=1
-- WHERE b.source_id=@srcid
-- AND b.changed=1
-- ;

-- Forget it, just mark all USDA species records instead
UPDATE cache a JOIN (
SELECT DISTINCT taxon
FROM distribution 
WHERE source_id=@srcid
) b
ON a.species=b.taxon 
SET del=1
;

-- Delete (after inspecting if desired)
DELETE FROM cache WHERE del=1;

--
-- Tidy up
-- 

ALTER TABLE distribution DROP COLUMN genus;
ALTER TABLE distribution DROP COLUMN changed;
ALTER TABLE cache DROP COLUMN del;
DROP TABLE distribution_usda_native_status_bak;
 