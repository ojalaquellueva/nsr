<?php

/////////////////////////////////////////////////////
// comma-delimited list of all checklist source codes
// for each country
/////////////////////////////////////////////////////

echo "Creating lookup table `country_sources`...";
$sql="
DROP TABLE IF EXISTS country_sources;
CREATE TABLE country_sources
SELECT country, CAST(GROUP_CONCAT(DISTINCT source_name SEPARATOR ', ') AS CHAR(250)) AS sources
FROM distribution d JOIN source s
ON d.source_id=s.source_id
WHERE is_comprehensive=1
GROUP BY country
;
ALTER TABLE country_sources
ADD PRIMARY KEY (country),
ADD INDEX (sources)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>