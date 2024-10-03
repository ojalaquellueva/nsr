<?php

///////////////////////////////////////////////////////
// Deletes rows not usable by NSR
///////////////////////////////////////////////////////

echo "  Deleting rows from `$tbl_raw` with no TDWG level 3 code...";
$sql="
DELETE FROM $tbl_raw
WHERE tdwgCodeL3 IS NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>