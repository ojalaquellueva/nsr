<?php

echo "Standardizing column `cult_status` in table `distribution`:\n";

echo "  Setting NULL `cult_status` to 'unknown'...";
$sql="
UPDATE distribution
SET cult_status='unknown'
WHERE cult_status IS NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>