<?php

///////////////////////////////////////////////////////////////////
// Delete temporary tables, if any
// Comment out if none
///////////////////////////////////////////////////////////////////

echo "Deleting raw data tables...";
$sql="
DROP TABLE IF EXISTS flbr_cclist_states;
DROP TABLE IF EXISTS flbr_dist_raw;
DROP TABLE IF EXISTS flbr_raw;
DROP TABLE IF EXISTS flbr_taxon_raw;
";
sql_execute_multiple($dbh, $sql);
echo $done;	

?>