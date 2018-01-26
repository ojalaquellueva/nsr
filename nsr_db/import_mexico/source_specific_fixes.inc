<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Removing bad records...";
$sql="
DELETE a.*
FROM `$tbl_raw` a JOIN `$tbl_species_raw` b
ON a.species_id=b.species_id
WHERE b.bad='BAD'
;
UPDATE `$tbl_raw` 
SET include=1
;
";
sql_execute_multiple($sql);
echo $done;

echo "  Populating taxon...";
$sql="
UPDATE `$tbl_raw` a JOIN `$tbl_species_raw` b
ON a.species_id=b.species_id
SET a.taxon=b.species,
a.species=b.species
;
";
sql_execute_multiple($sql);
echo $done;

echo "  Populating genus...";
$sql="
UPDATE `$tbl_raw`
SET genus=
CASE
WHEN species LIKE 'x %' THEN strSplit(species, ' ',2)
ELSE
strSplit(species, ' ',1)
END
;
";
sql_execute_multiple($sql);
echo $done;


?>