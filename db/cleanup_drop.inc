<?php

/////////////////////////////////////////////////////////
// Removes raw & staging tables if requested in 
// global_params.inc
/////////////////////////////////////////////////////////

echo "Dropping raw data tables...";
$sql="
SELECT CONCAT( 'DROP TABLE ', GROUP_CONCAT(table_name) , ';' ) 
AS statement FROM information_schema.tables 
WHERE table_schema = '$DB' AND table_name LIKE '%_raw'
;
";

if ( is_null( $qy=sql_get_first_result($dbh, $sql, 'statement') ) ) {
	echo "nothing to drop\n";
} else {
	sql_execute_multiple($dbh, $qy);	
	echo $done;	
}

echo "Dropping staging tables...";
$sql="
SELECT CONCAT( 'DROP TABLE ', GROUP_CONCAT(table_name) , ';' ) 
AS statement FROM information_schema.tables 
WHERE table_schema = '$DB' AND table_name LIKE '%_staging';
";

if ( is_null( $qy=sql_get_first_result($dbh, $sql, 'statement') ) ) {
	echo "nothing to drop\n";
} else {
	sql_execute_multiple($dbh, $qy);	
	echo $done;	
}

?>