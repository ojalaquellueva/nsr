-- get all distinct status values from raw data table

SELECT DISTINCT status FROM (
SELECT DISTINCT westIndies AS status FROM fwi_raw
UNION ALL 
SELECT DISTINCT greaterAntilles AS status FROM fwi_raw
UNION ALL 
SELECT DISTINCT jamaica AS status FROM fwi_raw
UNION ALL 
SELECT DISTINCT cuba AS status FROM fwi_raw
UNION ALL 
SELECT DISTINCT caymanIsland AS status FROM fwi_raw
UNION ALL 
SELECT DISTINCT hispaniola AS status FROM fwi_raw
UNION ALL 
SELECT DISTINCT puertoRico AS status FROM fwi_raw
UNION ALL 
SELECT DISTINCT virginIslands AS status FROM fwi_raw
UNION ALL 
SELECT DISTINCT bahamas AS status FROM fwi_raw
UNION ALL 
SELECT DISTINCT lesserAntillles AS status FROM fwi_raw
) AS a
ORDER BY status
;
