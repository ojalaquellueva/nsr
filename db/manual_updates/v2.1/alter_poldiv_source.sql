-- ----------------------------------------------------------
-- Updates to table poldiv_source to support spatial queries 
-- of political divisions
-- ----------------------------------------------------------

/* NOT YET ADDED TO PIPELINE! */

--
-- Create the gadm spatial object identifier columns
--
ALTER TABLE poldiv_source
ADD COLUMN gid_0 VARCHAR(12) DEFAULT NULL,
ADD COLUMN gid_1 VARCHAR(12) DEFAULT NULL,
ADD COLUMN gid_2 VARCHAR(12) DEFAULT NULL,
ADD COLUMN country VARCHAR(100) DEFAULT NULL
;

--
-- Populate the gadm spatial object identifier columns
--

-- Country via direct link to country
UPDATE poldiv_source ps JOIN country c
ON ps.poldiv_id=c.country_id
SET 
ps.gid_0=c.country_iso_alpha3, 
ps.country=c.country
WHERE poldiv_type='country'
;
-- Country via direct link to state_province
UPDATE poldiv_source ps JOIN state_province s
ON ps.poldiv_id=s.state_province_id
JOIN country c 
ON s.country_iso=c.country_iso
SET 
ps.gid_0=c.country_iso_alpha3,
ps.country=c.country
WHERE poldiv_type='state_province'
AND ps.gid_0 IS NULL
;


-- State
-- UNDER CONTRUCTION

--
-- Index the spatial object identifiers
--
ALTER TABLE poldiv_source ADD INDEX (gid_0);
ALTER TABLE poldiv_source ADD INDEX (gid_1);
ALTER TABLE poldiv_source ADD INDEX (gid_2);
ALTER TABLE poldiv_source ADD INDEX (country);



