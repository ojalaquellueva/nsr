-- ---------------------------------------------------------------
-- Compare content of two NSR databases
-- ---------------------------------------------------------------

-- Compare new database (nsr_dev) to previous (nsr_2_0)
USE nsr_dev;

SELECT dbold.source_name, dbnew.source_name, dbold, dbnew
FROM
(
SELECT source_name, COUNT(*) AS dbold
FROM nsr_2_0.source s LEFT JOIN nsr_2_0.distribution d
ON s.source_id=d.source_id
GROUP BY source_name
ORDER BY source_name
) AS dbold
LEFT JOIN 
(
SELECT source_name, COUNT(*) AS dbnew
FROM source s LEFT JOIN distribution d
ON s.source_id=d.source_id
GROUP BY source_name
ORDER BY source_name
) AS dbnew
ON dbold.source_name=dbnew.source_name
;