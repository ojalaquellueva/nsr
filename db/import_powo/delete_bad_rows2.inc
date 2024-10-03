<?php
///////////////////////////////////////////////////////
// Deletes rows not usable by NSR
///////////////////////////////////////////////////////

echo "  Deleting rows from `$tbl_raw` with no country...";
$sql="
ALTER TABLE $tbl_raw
ADD INDEX (country)
;
DELETE FROM $tbl_raw
WHERE country IS NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>