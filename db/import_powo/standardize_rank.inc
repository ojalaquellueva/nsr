<?php

//////////////////////////////////////////////////////////////////
// Detect rank of taxon
// Needed for parsing name from authors
//////////////////////////////////////////////////////////////////

echo "  Standardizing ranks:\r\n";

echo "    Standardizing values of `rank`...";
// Many more rank values than shown, but these can be used as-is
$sql="
UPDATE $tbl_raw
SET `rank`=
CASE
WHEN `rank`='Convariety' THEN 'convariety'
WHEN `rank`='Form' THEN 'forma'
WHEN `rank`='Genus' THEN 'genus'
WHEN `rank`='Species' THEN 'species'
WHEN `rank`='Subform' THEN 'subforma'
WHEN `rank`='Subspecies' THEN 'subspecies'
WHEN `rank`='Subvariety' THEN 'subvariety'
WHEN `rank`='Variety' THEN 'variety'
ELSE `rank`
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Filling missing values of `rank`...";
// just guess
$sql="
UPDATE $tbl_raw
SET `rank`='species'
WHERE `rank` IS NULL;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>