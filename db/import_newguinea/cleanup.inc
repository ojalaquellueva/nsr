<?php

echo "Deleting raw data tables...";

$sql="
DROP TABLE IF EXISTS 
newguinea_raw,
newguinea_raw_final,
newguinea_cclist_states
;	
";
sql_execute_multiple($dbh, $sql);
echo $done;	

?>