-- ------------------------------------------------------------------------
-- Adds missing state checklists
-- 2019-05-29
-- Update 2024-09-08: Added to DB pipeline, app & DB version 3.0
-- -------------------------------------------------------------------------

CREATE TABLE cclist_bak LIKE cclist;
INSERT INTO cclist_bak SELECT * FROM cclist;

INSERT INTO cclist (
country, state_province, county_parish
)
SELECT DISTINCT country, state_province_std, NULL
FROM state_province
WHERE country IN (
'Canada',
'United States',
'Mexico',
'Brazil',
'Argentina',
'Uruguay',
'Paraguay'
)
;

CREATE TABLE poldiv_source_bak LIKE poldiv_source;
INSERT INTO poldiv_source_bak SELECT * FROM poldiv_source;

INSERT INTO poldiv_source (
poldiv_id,
poldiv_name,
poldiv_type,
source_id,
checklist_type,
checklist_details
)
SELECT DISTINCT
a.state_province_id,
a.state_province_std,
'state_province',
b.source_id,
b.checklist_type,
b.checklist_details
FROM state_province a JOIN poldiv_source b
ON a.country=b.poldiv_name
WHERE a.country IN (
'Canada',
'United States',
'Mexico',
'Brazil',
'Argentina',
'Uruguay',
'Paraguay'
)
ORDER BY a.state_province_id
;

