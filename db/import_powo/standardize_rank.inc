<?php

//////////////////////////////////////////////////////////////////
// Detect rank of taxon
// Needed for parsing name from authors
//////////////////////////////////////////////////////////////////

echo "  Standardizing ranks:\r\n";

echo "    Column `rank`...";
$sql="
UPDATE $tbl_raw
SET `rank`=
CASE
WHEN `rank`='Form' THEN 'forma'
WHEN `rank`='GENUS' THEN 'genus'
WHEN `rank`='InfraspecificName' THEN 'infraspecific'
WHEN `rank`='SPECIES' THEN 'species'
WHEN `rank`='SUBSPECIES' THEN 'subspecies'
WHEN `rank`='VARIETY' THEN 'variety'
WHEN `rank`='Subvariety' THEN 'subvariety'
ELSE `rank`
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Column `accepted_rank`...";
$sql="
UPDATE $tbl_raw
SET accepted_rank=
CASE
WHEN accepted_rank='Form' THEN 'forma'
WHEN accepted_rank='GENUS' THEN 'genus'
WHEN accepted_rank='InfraspecificName' THEN 'infraspecific'
WHEN accepted_rank='SPECIES' THEN 'species'
WHEN accepted_rank='SUBSPECIES' THEN 'subspecies'
WHEN accepted_rank='VARIETY' THEN 'variety'
WHEN accepted_rank='Subvariety' THEN 'subvariety'
ELSE accepted_rank
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>