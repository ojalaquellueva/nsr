-- -------------------------------------
-- Presence
--
-- inherited upwards 
-- -------------------------------------

-- countyParish
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
AND o.county_parish=d.county_parish
SET 
o.native_status_country='P',
o.native_status_state_province='P',
o.native_status_county_parish='P'
WHERE 
d.native_status='unknown'
;

-- stateProvince
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
SET 
o.native_status_country='P',
o.native_status_state_province='P'
WHERE 
d.native_status='unknown'
;

-- countyParish
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
SET 
o.native_status_country='P'
WHERE 
d.native_status='unknown'
;

-- -------------------------------------
-- Native 
-- 
-- inherited upwards
-- trumps presence
-- -------------------------------------

-- countyParish
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
AND o.county_parish=d.county_parish
SET 
o.native_status_country='N',
o.native_status_state_province='N',
o.native_status_county_parish='N'
WHERE 
d.native_status='native'
;

-- stateProvince
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
SET 
o.native_status_country='N',
o.native_status_state_province='N'
WHERE 
d.native_status='native'
AND o.native_status IS NULL
AND o.county_parish IS NULL
;

-- countyParish
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
SET 
o.native_status_country='N'
WHERE 
d.native_status='native'
AND o.native_status IS NULL
AND o.county_parish IS NULL
AND o.state_province IS NULL
;

-- -------------------------------------
-- Introduced
--
-- Inherited downwards
-- trumps presence, native 
-- -------------------------------------

-- country
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
SET 
o.native_status_country='I',
o.native_status_state_province=IF(o.state_province IS NOT NULL, 'I',NULL),
o.native_status_county_parish=IF(o.county_parish IS NOT NULL, 'I', NULL)
WHERE 
d.native_status IN ('introduced','non-native','not native')
AND d.state_province IS NULL
AND d.county_parish IS NULL
;

-- stateProvince
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
SET 
o.native_status_state_province='I',
o.native_status_county_parish=IF(o.county_parish IS NOT NULL, 'I', NULL)
WHERE 
d.native_status IN ('introduced','non-native','not native')
AND d.county_parish IS NULL
;

-- county
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
AND o.county_parish=d.county_parish
SET 
o.native_status_county_parish='I'
WHERE 
d.native_status IN ('introduced','non-native','not native')
AND d.county_parish IS NULL
;

-- -------------------------------------
-- Endemic
--
-- Assign endemic status
-- species then families
-- -------------------------------------

-- countyParish
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
AND o.county_parish=d.county_parish
SET 
o.native_status_country='E',
o.native_status_state_province='E',
o.native_status_county_parish='E'
WHERE 
d.native_status='endemic'
;

-- stateProvince
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
SET 
o.native_status_country='E',
o.native_status_state_province='E'
WHERE 
d.native_status='endemic'
;

-- countyParish
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
SET 
o.native_status_country='E'
WHERE 
d.native_status='endemic'
;

-- countyParish
UPDATE observation o JOIN distribution d
ON o.family=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
AND o.county_parish=d.county_parish
SET 
o.native_status_country='E',
o.native_status_state_province='E',
o.native_status_county_parish='E'
WHERE 
d.native_status='endemic'
;

-- stateProvince
UPDATE observation o JOIN distribution d
ON o.family=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
SET 
o.native_status_country='E',
o.native_status_state_province='E'
WHERE 
d.native_status='endemic'
;

-- countyParish
UPDATE observation o JOIN distribution d
ON o.family=d.taxon
AND o.country=d.country
SET 
o.native_status_country='E'
WHERE 
d.native_status='endemic'
;

-- -------------------------------------
-- Endemic
--
-- Assign introduce status to endemic
-- species out of range
-- -------------------------------------

-- countyParish
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
SET 
o.native_status_country='Ie',
o.native_status_state_province='Ie',
o.native_status_county_parish='Ie'
WHERE 
d.native_status='endemic'
AND o.county_parish<>d.county_parish
;

-- stateProvince
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
SET 
o.native_status_country='Ie',
o.native_status_state_province='Ie',
o.native_status_county_parish=if(county_parish IS NULL, 'Ie', NULL)
WHERE 
d.native_status='endemic'
AND o.state_province<>d.state_province
;

-- countyParish
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
SET 
o.native_status_country='Ie',
o.native_status_state_province=IF(state_province IS NOT NULL, 'Ie', NULL),
o.native_status_county_parish=if(county_parish IS NOT NULL, 'Ie', NULL)
WHERE 
d.native_status='endemic'
AND o.country<>d.country
;

-- -------------------------------------
-- Endemic
--
-- Assign introduce status to endemic
-- genera out of range
-- -------------------------------------

-- countyParish
UPDATE observation o JOIN distribution d
ON o.genus=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
SET 
o.native_status_country='Ie',
o.native_status_state_province='Ie',
o.native_status_county_parish='Ie'
WHERE 
d.native_status='endemic'
AND o.county_parish<>d.county_parish
;

-- stateProvince
UPDATE observation o JOIN distribution d
ON o.genus=d.taxon
AND o.country=d.country
SET 
o.native_status_country='Ie',
o.native_status_state_province='Ie',
o.native_status_county_parish=if(county_parish IS NULL, 'Ie', NULL)
WHERE 
d.native_status='endemic'
AND o.state_province<>d.state_province
;

-- countyParish
UPDATE observation o JOIN distribution d
ON o.genus=d.taxon
SET 
o.native_status_country='Ie',
o.native_status_state_province=IF(state_province IS NOT NULL, 'Ie', NULL),
o.native_status_county_parish=if(county_parish IS NOT NULL, 'Ie', NULL)
WHERE 
d.native_status='endemic'
AND o.country<>d.country
;

-- -------------------------------------
-- Endemic
--
-- Assign introduce status to endemic
-- families out of range
-- -------------------------------------

-- countyParish
UPDATE observation o JOIN distribution d
ON o.family=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
SET 
o.native_status_country='Ie',
o.native_status_state_province='Ie',
o.native_status_county_parish='Ie'
WHERE 
d.native_status='endemic'
AND o.county_parish<>d.county_parish
;

-- stateProvince
UPDATE observation o JOIN distribution d
ON o.family=d.taxon
AND o.country=d.country
SET 
o.native_status_country='Ie',
o.native_status_state_province='Ie',
o.native_status_county_parish=if(county_parish IS NULL, 'Ie', NULL)
WHERE 
d.native_status='endemic'
AND o.state_province<>d.state_province
;

-- countyParish
UPDATE observation o JOIN distribution d
ON o.family=d.taxon
SET 
o.native_status_country='Ie',
o.native_status_state_province=IF(state_province IS NOT NULL, 'Ie', NULL),
o.native_status_county_parish=if(county_parish IS NOT NULL, 'Ie', NULL)
WHERE 
d.native_status='endemic'
AND o.country<>d.country
;