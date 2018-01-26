<?php

// Set NULL political divisions to empty strings so can 
// process in single pass
echo "    Setting NULL poldivs to empty string...";
$sql = "
UPDATE distribution_staging
SET 
country=IFNULL(country,''),
state_province=IFNULL(state_province,''),
county_parish=IFNULL(county_parish,'')
;
";
sql_execute_multiple($sql);
echo $done;

?>