<?php

/////////////////////////////////////////////////////////
// Combines raw data files into single file
// Each file is for a country, so need to populate
// country column on the fly
/////////////////////////////////////////////////////////

echo "  Combining raw data in table tropicos_raw...";
foreach($tbl_list as $tbl) {	
	$tbl_raw = $tbl."_raw";
	$ctry = ucfirst($tbl);
	//echo "  Inserting $tbl_raw...";
	
	$sql="
	INSERT INTO tropicos_raw (
	tropicos_id,
	country,
	taxon_with_author,
	status_verbatim
	)
	SELECT
	tropicos_id,
	'$ctry',
	species,
	status_verbatim
	FROM $tbl_raw
	WHERE species IS NOT NULL AND species<>''
	";
	sql_execute_multiple($sql);
	//echo $done;
}
echo $done;

?>