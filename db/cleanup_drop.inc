<?php

/////////////////////////////////////////////////////////
// Removes raw & staging tables if requested in 
// global_params.inc
/////////////////////////////////////////////////////////

echo "  Dropping raw data tables...";
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

echo "  Dropping staging tables...";
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

// Drop any remaining tables using source-specific 
// list of temporary tables
echo "  Dropping remaining temp tables by source:\n";

foreach ($src_array as $src) {
	echo "  ".$src."...";	
	unset($temp_file_list);
	include "import_".$src."/params.inc";
	
	if ( isset($temp_file_list) ) {
		$sql="
		SELECT CONCAT( 'DROP TABLE ', GROUP_CONCAT(table_name) , ';' ) 
		AS statement FROM information_schema.tables 
		WHERE table_schema = '$DB' AND table_name IN ($temp_file_list);
		";
		
		if ( is_null( $qy=sql_get_first_result($dbh, $sql, 'statement') ) ) {
			echo "nothing more to drop\n";
		} else {
			sql_execute_multiple($dbh, $qy);	
			echo $done;	
		}
	}
}

?>