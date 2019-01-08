<?php

/////////////////////////////////////////////////////
// comma-delimited list of all checklist source codes
// for each taxon
/////////////////////////////////////////////////////

echo "  Creating lookup table `taxon_country_sources`...";
$sql="
DROP TABLE IF EXISTS taxon_country_sources;
CREATE TABLE taxon_country_sources
SELECT 
taxon, country, native_status,
CAST(GROUP_CONCAT(DISTINCT source_name SEPARATOR ', ') AS CHAR(250)) AS sources
FROM distribution d JOIN source s
ON d.source_id=s.source_id
GROUP BY taxon, country, native_status
ORDER BY taxon, country, native_status
;
ALTER TABLE taxon_country_sources
ADD PRIMARY KEY (taxon, country, native_status),
ADD INDEX (taxon),
ADD INDEX (country),
ADD INDEX (native_status),
ADD INDEX (sources)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>