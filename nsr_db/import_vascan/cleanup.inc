<?php

///////////////////////////////////////////////////////////////////
// Delete temporary tables, if any
// Comment out if none
// Do not delete the raw table here; all raw tables can be deleted
// in a single step 
///////////////////////////////////////////////////////////////////

echo "Deleting temporary tables...";
$sql="
DROP TABLE IF EXISTS $tbl_vascan_taxon_raw;
DROP TABLE IF EXISTS $tbl_vascan_distribution_raw;
DROP TABLE IF EXISTS $tbl_raw;
";
sql_execute_multiple($dbh, $sql);
echo $done;	


?>