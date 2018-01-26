<?php

/////////////////////////////////////////////////////
// comma-delimited list of all checklist source codes
// for each taxon
/////////////////////////////////////////////////////

echo "  Creating lookup table `endemic_taxon_sources`...";
$sql="
DROP TABLE IF EXISTS endemic_taxon_sources;
CREATE TABLE endemic_taxon_sources
SELECT 
taxon, 
CAST(GROUP_CONCAT(DISTINCT source_name SEPARATOR ', ') AS CHAR(250)) AS sources
FROM distribution d JOIN source s
ON d.source_id=s.source_id
WHERE d.native_status='endemic'
GROUP BY taxon
;
ALTER TABLE endemic_taxon_sources
ADD PRIMARY KEY (taxon),
ADD INDEX (sources)
;
";
sql_execute_multiple($sql);
echo $done;

?>