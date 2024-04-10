<?php

/////////////////////////////////////////////////////////
// Mark duplicate taxon + political division combinations
// for removal
/////////////////////////////////////////////////////////

echo "Marking duplicate records:\r\n";

echo "  Creating indexes...";
$sql="
ALTER TABLE $tbl_raw
ADD INDEX (country),
ADD INDEX (poldiv_full)
; 
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Setting missing values of `country` to NULL...";
$sql="
UPDATE $tbl_raw
SET country=NULL
WHERE TRIM(country)=''
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Adding column `is_dupe`...";
$sql="
ALTER TABLE $tbl_raw
ADD COLUMN is_dupe INT(1) DEFAULT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Setting default value of `is_dupe` for non-NULL country...";
$sql="
UPDATE $tbl_raw
SET is_dupe=1
WHERE country IS NOT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Marking duplicate records...";
$sql="
UPDATE $tbl_raw r JOIN
(
SELECT 
poldiv_full,
name, 
(
SELECT id
FROM $tbl_raw r
WHERE $tbl_raw.name=r.name AND $tbl_raw.poldiv_full=r.poldiv_full
ORDER BY id
LIMIT 1
) AS first_id
FROM $tbl_raw
GROUP BY poldiv_full, name
) AS nodupes
ON r.id=nodupes.first_id
SET is_dupe=0
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Adding remaining indexes...";
$sql="
ALTER TABLE $tbl_raw
ADD INDEX (is_dupe)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>