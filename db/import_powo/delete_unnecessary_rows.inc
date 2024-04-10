<?php

///////////////////////////////////////////////////////
// Deletes rows not needed for NSR
///////////////////////////////////////////////////////


echo "  Removing unnecessary rows:\r\n";

echo "    area_name IS NULL...";
$sql="
DELETE FROM $tbl_raw
WHERE area_name IS NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>