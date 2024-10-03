<?php

/////////////////////////////////////////////////////////
// Move temp tables to schema $DB."_staging"
/////////////////////////////////////////////////////////

//
// Determine if new staging database should be created
//

$db_exists=db_exists($db_staging, $USER, $PWD);		

if ( $DB_STAGING_REPLACE==FALSE && $db_exists ) {
	$create_db_staging=FALSE;	
} else {
	$create_db_staging=TRUE;
}

//
// Create new staging database if applicable
//

if ( $create_db_staging==TRUE ) {
	include "mysql_connect.inc";	// Connect without specifying database
	
	// Drop and replace entire database
	echo "  Creating database `$db_staging`...";
	$sql_create_db="
		DROP DATABASE IF EXISTS `".$db_staging."`;
		CREATE DATABASE `".$db_staging."`;
		USE `".$db_staging."`;
	";
	sql_execute_multiple($dbm, $sql_create_db);
	echo "done\n";
	mysqli_close($dbm);
}
	
//
// Move tables with suffixes "_raw" and "_staging"
//

echo "  Moving raw and staging tables...";
$old_db=$DB;
$new_db=$db_staging;

$sql_temp_tables="
SELECT table_name
FROM information_schema.tables 
WHERE table_schema = '$old_db' 
AND (table_name LIKE '%_raw' OR table_name LIKE '%_raw_%'
OR table_name LIKE '%_staging' OR table_name LIKE '%_staging_%' 
OR table_name LIKE '%_temp' OR table_name LIKE 'temp_%' )
;

;
";

if ( is_null( $qy=sql_get_first_result($dbh, $sql_temp_tables, 'TABLE_NAME') ) ) {
	echo "nothing to move\n";
} else {
	$qy_temp_tables = mysqli_query($dbh,$sql_temp_tables);
	while ($row = mysqli_fetch_assoc($qy_temp_tables)) {
		$tbl = $row['TABLE_NAME'];		// note caps
		$sql="DROP TABLE IF EXISTS ".$new_db.".".$tbl.";";		
		sql_execute_multiple($dbh, $sql);
		$sql="ALTER TABLE ".$old_db.".".$tbl." RENAME ".$new_db.".".$tbl.";";		
		sql_execute_multiple($dbh, $sql);
	}
	echo $done;
}


//
// Move remaining tables, if any
//

echo "  Moving remaining temp tables by source:\n";

foreach ($src_array as $src) {
	echo "    ".$src."...";	
	unset($temp_tbl_list);
	include "import_".$src."/params.inc";
	
	if ( isset($temp_tbl_list) ) {
		$sql_temp_tables="
		SELECT table_name
		FROM information_schema.tables 
		WHERE table_schema = '$old_db' 
		AND table_name IN ($temp_tbl_list)
		;
		";
		
		if ( is_null( $qy=sql_get_first_result($dbh, $sql_temp_tables, 'TABLE_NAME') ) ) {
			echo "nothing more to drop\n";
		} else {
			$qy_temp_tables = mysqli_query($dbh,$sql_temp_tables);
			while ($row = mysqli_fetch_assoc($qy_temp_tables)) {
				$tbl = $row['TABLE_NAME'];		// note caps
				$sql="DROP TABLE IF EXISTS ".$new_db.".".$tbl.";";		
				sql_execute_multiple($dbh, $sql);
				$sql="ALTER TABLE ".$old_db.".".$tbl." RENAME ".$new_db.".".$tbl.";";		
				sql_execute_multiple($dbh, $sql);
			}
			echo $done;
		}
	} else {
		echo "parameter \$temp_tbl_list not set for this source\n";
	}
}

?>