<?php

echo "Deleting raw data tables...";
foreach($tbl_list as $tbl) {	
	$tbl_raw = $tbl."_raw";
	//echo "  $tbl_raw...";
	$sql="
	DROP TABLE $tbl_raw;	
	";
	sql_execute_multiple($dbh, $sql);
}

$sql="
DROP TABLE tropicos_raw;	
";
sql_execute_multiple($dbh, $sql);
echo $done;	



?>