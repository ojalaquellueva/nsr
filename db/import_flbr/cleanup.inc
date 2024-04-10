<?php

///////////////////////////////////////////////////////////////////
// Delete temporary tables, if any
// Comment out if none
///////////////////////////////////////////////////////////////////

echo "Deleting raw data tables...";
$sql="
DROP TABLE IF EXISTS mexico_raw;
DROP TABLE IF EXISTS mexico_species_raw;
";
sql_execute_multiple($dbh, $sql);
echo $done;	


?>