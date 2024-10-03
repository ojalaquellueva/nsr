-- 
-- Check for missing names
--

SELECT COUNT(*)
FROM powo_combined_raw
WHERE plant_name_id IS NULL or name IS NULL
;
/*
+----------+
| COUNT(*) |
+----------+
|        0 |
+----------+
1 row in set (1.70 sec)
*** All good ***
*/

-- 
-- Check for names that area synonyms (have accepted name)
--

SELECT COUNT(*)
FROM powo_combined_raw
WHERE NOT accepted_plant_name_id=plant_name_id
;
/*
+----------+
| COUNT(*) |
+----------+
|        0 |
+----------+
1 row in set (1.70 sec)
*** All good ***
*/

--
-- Check taxonomicStatus of names in final combined_raw table
--

SELECT taxonomicStatus, COUNT(*)
FROM powo_combined_raw
GROUP BY taxonomicStatus
ORDER BY taxonomicStatus
;
/*
+-----------------+----------+
| taxonomicStatus | COUNT(*) |
+-----------------+----------+
| Accepted        |  1956990 |
| Local Biotype   |     1095 |
| Unplaced        |    12167 |
+-----------------+----------+
3 rows in set (3.20 sec)
OK, as long as none are synonyms...
*/

-- 
-- Check for names that area synonyms (have accepted name)
--

SELECT COUNT(*)
FROM powo_combined_raw
WHERE NOT accepted_plant_name_id=plant_name_id
;
/*
+----------+
| COUNT(*) |
+----------+
|        0 |
+----------+
1 row in set (1.70 sec)
*** All good ***
*/

--
-- Check for missing region codes
-- 

SELECT COUNT(*)
FROM powo_combined_raw
WHERE tdwgCodeL3 IS NULL
;
/*
+----------+
| COUNT(*) |
+----------+
|     1329 |
+----------+
1 row in set (1.65 sec)
*** Not good, investigate further
*/

--
--  Confirm that all code in combined_raw table are TDWG level three codes
--

SELECT tdwgCodeL3, area_name, COUNT(*)
FROM powo_combined_raw
GROUP BY tdwgCodeL3, area_name
ORDER BY tdwgCodeL3, area_name
;
/*

All good, except for the NULLs
+------------+----------------------+----------+
| tdwgCodeL3 | area_name            | COUNT(*) |
+------------+----------------------+----------+
| NULL       | NULL                 |     1329 |
| ABT        | Alberta              |     3244 |
| AFG        | Afghanistan          |     6600 |
| AGE        | Argentina Northeast  |     8878 |
| AGS        | Argentina South      |     3798 |
[...]
*/

--
-- Examine rows in with missing regions codes
-- 

SELECT family, name, powo_plant_locality_id, tdwgCodeL3, area_name, introduced, extinct, location_doubtful
FROM powo_combined_raw
WHERE tdwgCodeL3 IS NULL
;
/*
Empty set (0.01 sec)
*/


--
-- Examine rows in raw distribution table with missing regions codes
-- 

SELECT continent_code_l1, continent, region_code_l2, region, tdwgCodeL3, area 
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NULL 
LIMIT 6;
/*
+-------------------+------------------+----------------+-----------------------+------------+------+
| continent_code_l1 | continent        | region_code_l2 | region                | tdwgCodeL3 | area |
+-------------------+------------------+----------------+-----------------------+------------+------+
| 8                 | SOUTHERN AMERICA | 83             | Western South America | NULL       | NULL |
| 8                 | SOUTHERN AMERICA | 83             | Western South America | NULL       | NULL |
| 8                 | SOUTHERN AMERICA | 83             | Western South America | NULL       | NULL |
| 8                 | SOUTHERN AMERICA | 83             | Western South America | NULL       | NULL |
| 8                 | SOUTHERN AMERICA | 83             | Western South America | NULL       | NULL |
| 8                 | SOUTHERN AMERICA | 83             | Western South America | NULL       | NULL |
+-------------------+------------------+----------------+-----------------------+------------+------+
6 rows in set (0.02 sec)
*** Some species distributions are coded as the l2 level only
*/

--
-- Find out how many species distributions are l1-only, l2-only, and l3
-- 

SELECT 'No code' AS TDWG_code_level, COUNT(*) AS species_distributions
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NULL AND continent_code_l1 IS NULL 
UNION ALL
SELECT 'l1 only', COUNT(*)
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NULL AND continent_code_l1 IS NOT NULL 
UNION ALL
SELECT 'l2 only', COUNT(*)
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NOT NULL
UNION ALL
SELECT 'l3', COUNT(*)
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NOT NULL
;
/*
+-----------------+-----------------------+
| TDWG_code_level | species_distributions |
+-----------------+-----------------------+
| No code         |                     0 |
| l1 only         |                   105 |
| l2 only         |                  1224 |
| l3              |               1968923 |
+-----------------+-----------------------+
4 rows in set (3.10 sec)
*/

--
-- Count taxa which are null, l1-only, l2-only, and l3
-- 

SELECT 'No code' AS TDWG_code_level, COUNT(DISTINCT plant_name_id) AS count_of_taxa
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NULL AND continent_code_l1 IS NULL 
UNION ALL
SELECT 'l1 only', COUNT(DISTINCT plant_name_id)
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NULL AND continent_code_l1 IS NOT NULL 
UNION ALL
SELECT 'l2 only', COUNT(DISTINCT plant_name_id)
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NOT NULL
UNION ALL
SELECT 'l3', COUNT(DISTINCT plant_name_id)
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NOT NULL
;


--
-- List counts of unique l1- and l2-only code combinations
-- = # of distributions that need to be unpacked into component countries
--

SELECT 'l1 only' AS Distinct_TDWG_codes, COUNT(*) 
FROM (
SELECT DISTINCT continent_code_l1 
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NULL AND continent_code_l1 IS NOT NULL 
) a
UNION ALL
SELECT 'l2 only', COUNT(*)
FROM (
SELECT DISTINCT continent_code_l1, region_code_l2
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NOT NULL
) b
;
/*
+---------------------+----------+
| Distinct_TDWG_codes | COUNT(*) |
+---------------------+----------+
| l1 only             |        5 |
| l2 only             |       37 |
+---------------------+----------+
2 rows in set (1.87 sec)
*/

--
-- List distinct l1- and l2-only codes
--

-- l1-only codes
SELECT DISTINCT continent_code_l1, continent
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NULL AND continent_code_l1 IS NOT NULL
ORDER BY continent_code_l1, continent
;
/*
+-------------------+------------------+
| continent_code_l1 | continent        |
+-------------------+------------------+
| 1                 | EUROPE           |
| 2                 | AFRICA           |
| 4                 | ASIA-TROPICAL    |
| 7                 | NORTHERN AMERICA |
| 8                 | SOUTHERN AMERICA |
+-------------------+------------------+
5 rows in set (1.06 sec)
*/
 
-- l2-only codes
SELECT DISTINCT continent_code_l1, continent, region_code_l2, region
FROM powo_distribution_raw 
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NOT NULL
ORDER BY continent_code_l1, continent, region_code_l2, region
;

--
-- List example species which are l1 and l2-only 
--

SELECT DISTINCT family, taxon_name AS taxon, taxon_status, introduced, continent_code_l1, continent
FROM powo_names_raw n JOIN powo_distribution_raw d
ON n.plant_name_id=d.plant_name_id
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NULL AND continent_code_l1 IS NOT NULL
ORDER BY family, taxon_name
LIMIT 6
;


SELECT DISTINCT family, taxon_name AS taxon, taxon_status, introduced, 
continent_code_l1, continent, region_code_l2, region
FROM powo_names_raw n JOIN powo_distribution_raw d
ON n.plant_name_id=d.plant_name_id
WHERE tdwgCodeL3 IS NULL AND region_code_l2 IS NOT NULL AND continent_code_l1 IS NOT NULL
ORDER BY family, taxon_name
LIMIT 6
;


--
-- Examine regions and counts of species for which l3 codes cannot be resolved
--

-- Region count
SELECT COUNT(*) 
FROM powo_region_codes 
WHERE code_type='3-letter alphabetic' AND country IS NULL
;
/*
+----------+
| count(*) |
+----------+
|        7 |
+----------+
1 row in set (0.01 sec)
*/

-- Regions
SELECT code, region
FROM powo_region_codes 
WHERE code_type='3-letter alphabetic' AND country IS NULL
;
/*
+------+------------------------------+
| code | region                       |
+------+------------------------------+
| GGI  | Gulf of Guinea Is.           |
| SCS  | South China Sea              |
| CPI  | Central American Pacific Is. |
| LEE  | Leeward Is.                  |
| NLA  | Netherlands Antilles         |
| SWC  | Southwest Caribbean          |
| WIN  | Windward Is.                 |
+------+------------------------------+
7 rows in set (0.00 sec)
*/

-- Count of regions linked to species distributions
SELECT COUNT(DISTINCT r.code) AS tdwgCodeL3_codes
FROM powo_names_raw n JOIN powo_distribution_raw d
ON n.plant_name_id=d.plant_name_id
JOIN powo_region_codes r
ON d.tdwgCodeL3=r.code
WHERE d.tdwgCodeL3 IS NOT NULL AND r.country IS NULL
;
/*
+------------------+
| tdwgCodeL3_codes |
+------------------+
|                7 |
+------------------+
1 row in set (8.19 sec)
*** As expected; agrees with the above query
*/

-- Species distribution assertions count
SELECT COUNT(DISTINCT d.plant_locality_id) AS distribution_assertions
FROM powo_names_raw n JOIN powo_distribution_raw d
ON n.plant_name_id=d.plant_name_id
JOIN powo_region_codes r
ON d.tdwgCodeL3=r.code
WHERE tdwgCodeL3 IS NOT NULL AND r.country IS NULL
;
/*
+-------------------------+
| distribution_assertions |
+-------------------------+
|                   15204 |
+-------------------------+
1 row in set (7.92 sec)
*/

-- Species count
SELECT COUNT(DISTINCT n.taxon_name) AS taxa
FROM powo_names_raw n JOIN powo_distribution_raw d
ON n.plant_name_id=d.plant_name_id
JOIN powo_region_codes r
ON d.tdwgCodeL3=r.code
WHERE tdwgCodeL3 IS NOT NULL AND r.country IS NULL
;
/*
+------+
| taxa |
+------+
| 8449 |
+------+
1 row in set (7.77 sec)
*** Quite a few...but most are Caribbean, and therefore covered by source fwi
*/

-- Above species which are Caribbean
SELECT COUNT(DISTINCT n.taxon_name) AS taxa
FROM powo_names_raw n JOIN powo_distribution_raw d
ON n.plant_name_id=d.plant_name_id
JOIN powo_region_codes r
ON d.tdwgCodeL3=r.code
WHERE tdwgCodeL3 IS NOT NULL AND r.country IS NULL
AND CODE IN ('LEE','NLA','SWC','WIN')
;
/*
+------+
| taxa |
+------+
| 5464 |
+------+
1 row in set (1.18 sec)
*/

-- Above species which are NOT Caribbean
SELECT COUNT(DISTINCT n.taxon_name) AS taxa
FROM powo_names_raw n JOIN powo_distribution_raw d
ON n.plant_name_id=d.plant_name_id
JOIN powo_region_codes r
ON d.tdwgCodeL3=r.code
WHERE tdwgCodeL3 IS NOT NULL AND r.country IS NULL
AND NOT CODE IN ('LEE','NLA','SWC','WIN')
;
/*
+------+
| taxa |
+------+
| 4330 |
+------+
1 row in set (8.21 sec)
*/

-- Check example species which are not Caribbean
SELECT DISTINCT family, taxon_name AS taxon, taxon_status
FROM powo_names_raw n JOIN powo_distribution_raw d
ON n.plant_name_id=d.plant_name_id
JOIN powo_region_codes r
ON d.tdwgCodeL3=r.code
WHERE tdwgCodeL3 IS NOT NULL AND r.country IS NULL
AND NOT CODE IN ('LEE','NLA','SWC','WIN')
ORDER BY family, taxon_name
LIMIT 25
;

SELECT taxon_status, COUNT(*)
FROM powo_names_raw n JOIN powo_distribution_raw d
ON n.plant_name_id=d.plant_name_id
JOIN powo_region_codes r
ON d.tdwgCodeL3=r.code
WHERE tdwgCodeL3 IS NOT NULL AND r.country IS NULL
AND NOT CODE IN ('LEE','NLA','SWC','WIN')
GROUP BY taxon_status
ORDER BY taxon_status
;
/*
+--------------+----------+
| taxon_status | COUNT(*) |
+--------------+----------+
| Accepted     |     4804 |
| Unplaced     |       11 |
+--------------+----------+
2 rows in set (9.50 sec)


-- -------------------------------------------------------------
-- Final conclusions
-- -------------------------------------------------------------
/*
Inspecting the above two queries, the vast majority of species without a code at the l3
level are poorly known species of tropical regions. Almost all have taxonomicStatus=
'Unknown'. In other words, most are 'Unresolved' names. Checking the Kew/POWO website, 
every one of the above species does not have a distribution map. The only distribution 
information provided is the following statement appearing below the species name: 

"The native range of this species is likely to be <l1 or l2 region>."

Bottom line: these species do not have usable distribution information, and can therefore
be treated the same as species with all NULL distribution codes, and deleted from
the POWO data extract

Finally, regarding the ~8,400 species with a TDWG l3 code which is not resolved to
country, 5,464 are Caribbean and therefore covered by fwi. However, the remaining 4,804
non-Caribbean species are almost all good, accepted species. Therefore, at least the
non-Caribbean l3 codes snould be resolved to countries. These are:

+------+------------------------------+
| code | region                       |
+------+------------------------------+
| GGI  | Gulf of Guinea Is.           |
| SCS  | South China Sea              |
| CPI  | Central American Pacific Is. |
+------+------------------------------+






