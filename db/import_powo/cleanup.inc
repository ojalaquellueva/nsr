<?php

echo "Deleting raw data tables...";

$sql="
DROP TABLE IF EXISTS 
powo_raw, 
powo_poldivs, 
powo_poldivs_gnrs, 
powo_region_codes, 
powo_regions,
powo_cclist_states
;	
";
sql_execute_multiple($dbh, $sql);
echo $done;	



?>