<?php

/////////////////////////////////////////////////////////
// Removes raw & staging tables if requested in 
// global_params.inc
/////////////////////////////////////////////////////////

if ($drop_raw_force) {
	echo "Dropping raw data tables...";
	
	$sql="
	SELECT CONCAT( 'DROP TABLE ', GROUP_CONCAT(table_name) , ';' ) 
    AS statement FROM information_schema.tables 
    WHERE table_schema = '$DB' AND table_name LIKE '%_raw';
    ";
    $qy=sql_get_first_result($sql,'statement');
    //echo "SQL:\r\n".$qy."\r\n";
	sql_execute_multiple($qy);	
	echo $done;	
}

if ($drop_staging_force) {
	echo "Dropping staging tables...";
	
	$sql="
	SELECT CONCAT( 'DROP TABLE ', GROUP_CONCAT(table_name) , ';' ) 
    AS statement FROM information_schema.tables 
    WHERE table_schema = '$DB' AND table_name LIKE '%_staging';
    ";
    $qy=sql_get_first_result($sql,'statement');
    //echo "SQL:\r\n".$qy."\r\n";
	sql_execute_multiple($qy);	
	echo $done;	
}


?>