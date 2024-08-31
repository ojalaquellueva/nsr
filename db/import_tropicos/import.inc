<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by
// and $ignore_lines are set in parameters file

echo "Loading raw data:\r\n";

/* NOTE
Did not attempt to implement $ROW_LIMIT for this source. Too complex, given
the links between tables
Need to separate tropicos into three sources, one per country!!
*/

foreach($tbl_list as $tbl) {	
	$tbl_raw = $tbl."_raw";
	$file_raw = $tbl.$file_ext;
	echo "  File $file_raw to table `$tbl_raw`...";
	$sql = "
	LOAD DATA $local INFILE '$datapath$file_raw' 
	INTO TABLE $tbl_raw 
	$character_set 
	$fields_terminated_by 
	$optionally_enclosed_by 
	$lines_terminated_by 
	$ignore_lines;
	";
	sql_execute_multiple($dbh, $sql);
	if (!(empty_string_to_null($dbh, $tbl_raw))) die("Error\r\n.");
	echo $done;
}


?>
