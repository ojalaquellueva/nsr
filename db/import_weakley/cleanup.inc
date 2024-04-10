<?php

///////////////////////////////////////////////////////////////////
// Delete temporary tables, if any
// Comment out if none
// Do not delete the raw table here; all raw tables can be deleted
// in a single step 
///////////////////////////////////////////////////////////////////

echo "Deleting temporary tables...";
$sql="
DROP TABLE IF EXISTS $tbl_raw;
DROP TABLE IF EXISTS $tbl_weakley_exotic_all_raw;
DROP TABLE IF EXISTS $tbl_weakley_exotic_part_raw;
DROP TABLE IF EXISTS $tbl_weakley_origin_raw;
DROP TABLE IF EXISTS $tbl_weakley_poldivs_raw;
";
sql_execute_multiple($dbh, $sql);
echo $done;	


?>