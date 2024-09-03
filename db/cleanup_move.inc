<?php

/////////////////////////////////////////////////////////
// Move raw & staging tables to schema $DB."_staging"
// $DB . "_staging" must exist
/////////////////////////////////////////////////////////

$old_db=$DB;
$new_db=$DB."_staging";

echo "Moving tables...";
$sql_temp_tables = mysqli_query($dbh, "
SELECT table_name
FROM information_schema.tables 
WHERE table_schema = '$old_db' 
AND (table_name LIKE '%_raw' OR table_name LIKE '%_staging')
;
");

while ($row = mysqli_fetch_assoc($sql_temp_tables)) {
	$tbl = $row['TABLE_NAME'];		// note caps
	$sql="ALTER TABLE " . $old_db . "." . $tbl . " RENAME " . $new_db . "." . $tbl . ";";		
	sql_execute_multiple($dbh, $sql);
}
echo $done;

?>