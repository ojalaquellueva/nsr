<?php

/////////////////////////////////////////////////////////
// Move raw & staging tables to schema $DB."_staging"
// $DB . "_staging" must exist
/////////////////////////////////////////////////////////

$old_db=$DB;
$new_db=$DB."_staging";

echo "Moving raw and staging tables...";
$sql_temp_tables="
SELECT table_name
FROM information_schema.tables 
WHERE table_schema = '$old_db' 
AND (table_name LIKE '%_raw' OR table_name LIKE '%_staging')
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


echo "Moving remaining temp tables by source:\n";

foreach ($src_array as $src) {
	echo "  ".$src."...";	
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