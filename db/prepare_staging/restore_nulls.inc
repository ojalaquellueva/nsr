<?php

// Restore NULLs
echo "    Restoring NULLs...";
$sql="
UPDATE distribution_staging
SET country=IF(country='',NULL,country),
state_province=IF(state_province='',NULL,state_province),
county_parish=IF(county_parish='',NULL,county_parish)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>