<?php

///////////////////////////////////////////////
// Normalizes multiple occurrence columns into
// a single status column
///////////////////////////////////////////////

echo "Normalizing occurrences:\r\n";

// Loop through each record of raw table
$sql_region="
SELECT DISTINCT region
FROM fwi_regions_raw
;
";
$regions = mysqli_query($dbh, $sql_region);

// Process each region
while ($row = mysqli_fetch_assoc($regions)) {	
	$region = $row["region"];
	$region_col = $region;

	echo "  $region...";
		
	// Insert region_country combinations
	$sql = "
	INSERT INTO fwi_occurrences (
	source_name,
	region,
	family,
	genus,
	species,
	taxon,
	taxon_rank,
	status_verbatim
	)
	SELECT 
	'$src',
	'$region',
	family,
	genus,
	TRIM(CONCAT_WS(' ',IFNULL(genus,''),IFNULL(epithet,''))),
	taxon,
	taxon_rank,
	$region_col
	FROM fwi_raw 
	;
	";

	// add record to new table
	sql_execute_multiple($dbh, $sql);	
	echo $done;
}

?>