<?php

///////////////////////////////////////////////////
// Populates table gf_lookup
//
// Requires local databases:
//	gf_lookup
//	tnrs4
///////////////////////////////////////////////////

$db_gf_lookup="gf_lookup";
$db_tnrs="tnrs4";

echo "Populating table gf_lookup:\r\n";

echo "  Source: gf_lookup...";
$sql="
INSERT INTO gf_lookup (
genus,
family,
source
) 
SELECT 
genus,
family,
'gf_lookup'
FROM $db_gf_lookup.genus_family
WHERE isAccepted=1
;
";
sql_execute_multiple($sql);	
echo $done;

echo "  Source: tnrs (accepted)...";
$sql="
INSERT INTO gf_lookup (
genus,
family,
source
) 
SELECT DISTINCT 
scientificName,
family,
'tnrs (accepted)'
FROM $db_tnrs.name a join $db_tnrs.higherClassification b 
ON a.nameID=b.nameID 
JOIN $db_tnrs.synonym c ON a.nameID=c.nameID 
WHERE classificationSourceID=4 
AND nameRank='genus' 
AND family IS NOT NULL 
AND acceptance in ('Accepted')
;
";
sql_execute_multiple($sql);	
echo $done;

echo "  Source: tnrs (all)...";
$sql="
INSERT INTO gf_lookup (
genus,
family,
source
) 
SELECT DISTINCT 
scientificName,
family,
'tnrs (all)'
FROM $db_tnrs.name a join $db_tnrs.higherClassification b 
ON a.nameID=b.nameID 
WHERE classificationSourceID=4 
AND nameRank='genus' 
AND family IS NOT NULL 
;
";
sql_execute_multiple($sql);	
echo $done;

echo "  Indexing...";
$sql="
ALTER TABLE gf_lookup 
ADD INDEX (genus),
ADD INDEX (family),
ADD INDEX (source)
;
";
sql_execute_multiple($sql);	
echo $done;

echo "  Removing duplicates...";
$sql="
UPDATE gf_lookup a JOIN gf_lookup b
ON a.genus=b.genus
SET b.source='duplicate'
WHERE a.source='gf_lookup'
AND b.source='tnrs (accepted)'
;
DELETE FROM gf_lookup
WHERE source='duplicate'
;
UPDATE gf_lookup a JOIN gf_lookup b
ON a.genus=b.genus
SET b.source='duplicate'
WHERE a.source IN ('gf_lookup','tnrs (accepted)')
AND b.source='tnrs (all)'
;
DELETE FROM gf_lookup
WHERE source='duplicate'
;
";
sql_execute_multiple($sql);	
echo $done;



?>