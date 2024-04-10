-- Queries of table observation
SELECT family, species, country, state_province, county_parish,
native_status_country AS ns_country,
native_status_state_province AS ns_state_province, 
native_status_county_parish AS ns_county_parish,
native_status
FROM observation
LIMIT 25;

SELECT DISTINCT 
native_status_country AS ns_country,
native_status_state_province AS ns_state_province, 
native_status_county_parish AS ns_county_parish
FROM observation;

SELECT 
country,
native_status_country AS ns_country,
native_status_state_province AS ns_state_province, 
native_status_county_parish AS ns_county_parish,
COUNT(*) AS obs
FROM observation
GROUP BY 
country,
native_status_country,
native_status_state_province, 
native_status_county_parish;

SELECT 
country,
native_status_country AS ns_country,
native_status_state_province AS ns_state_province, 
native_status_county_parish AS ns_county_parish,
native_status,
COUNT(*) AS obs
FROM observation
GROUP BY 
country,
native_status_country,
native_status_state_province, 
native_status_county_parish,
native_status;




-- Example test queries of observations against checklists

-- check of status in same region (country-level)
-- This may return multiple records per species if more than one source
-- for this contry
SELECT DISTINCT o.country, o.species, d.native_status, d.cult_status, 
d.source_name, d.is_comprehensive
FROM observation o LEFT JOIN 
(
SELECT taxon, country,
source_name, is_comprehensive, native_status, cult_status
FROM distribution d JOIN source s
ON d.source_id=s.source_id
) AS d
ON o.species=d.taxon AND o.country=d.country
ORDER BY o.country, o.species, d.native_status, d.cult_status
;

-- check of status in all regions (country-level)
SELECT DISTINCT o.country as observation_country, d.country AS checklist_country, 
o.species, d.native_status AS checklist_country_native_status, 
d.cult_status AS checklist_country_cult_status, 
d.source_name, d.is_comprehensive
FROM observation o LEFT JOIN 
(
SELECT taxon, country,
source_name, is_comprehensive, native_status, cult_status
FROM distribution d JOIN source s
ON d.source_id=s.source_id
) AS d
ON o.species=d.taxon
ORDER BY o.species, o.country, d.country, d.native_status, d.cult_status
;

-- check for endemism in other country
SELECT DISTINCT o.country as observation_country, d.country AS endemic_country, 
o.species, d.native_status, d.cult_status, 
d.source_name, d.is_comprehensive
FROM observation o JOIN 
(
SELECT taxon, country,
source_name, is_comprehensive, native_status, cult_status
FROM distribution d JOIN source s
ON d.source_id=s.source_id
) AS d
ON o.species=d.taxon 
WHERE o.country<>d.country
AND d.native_status='endemic'
ORDER BY o.country, o.species, d.native_status, d.cult_status
;
