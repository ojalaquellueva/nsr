<?php

///////////////////////////////////////////////////////////////////
// Delete temporary tables, if any
// Comment out if none
// Do not delete the raw table here; all raw tables can be deleted
// in a single step 
///////////////////////////////////////////////////////////////////

echo "Deleting temporary tables...";
$sql="
DROP TABLE IF EXISTS fwi_raw;
DROP TABLE IF EXISTS fwi_regions_raw;
DROP TABLE IF EXISTS fwi_region_country;
DROP TABLE IF EXISTS fwi_country;
DROP TABLE IF EXISTS fwi_temp;
DROP TABLE IF EXISTS fwi;
";
sql_execute_multiple($sql);
echo $done;	


?>