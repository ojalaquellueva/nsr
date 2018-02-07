<?php

/////////////////////////////////////////////////////////
// Removes raw data tables if this requested in 
// global_params.inc
/////////////////////////////////////////////////////////

if ($drop_raw) {
	echo "Dropping raw data tables...";
	
	foreach ($src_array as $src) {
		$tbl_raw = $src . "_raw";
		$sql = "
		DROP TABLE IF EXISTS `$tbl_raw`;		
		";	
		$tbl_raw = "raw_" . $src;
		$sql = "
		DROP TABLE IF EXISTS `$tbl_raw`;		
		";		
	}
	
	$done;
}

?>