<?php

//////////////////////////////////////////////////////
// Standardized status codes in raw data
// leave blank if raw table does not have status
// codes; populate fixed status codes when load to
// staging table in final step
//////////////////////////////////////////////////////

echo "Populating native status (all endemic)...";
$sql="
UPDATE $tbl_raw
SET native_status='endemic'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>