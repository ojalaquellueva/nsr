<?php

/////////////////////////////////////////////////////
// Flags a species as absent in all countries not
// in region of endemism. 
// This is only safe way to interpret assertions of
// a species being endemic to a multi-country region. 
// Can't definitively mark such species as endemic or
// even present in all countries comprising that region. 
// Would end up marking dozens of Cuban endemics as
// present on other West Indian islands where they 
// do not occur. But can at least mark these same 
// species as absent from all other
// countries.
// Note that we can do nothing with species listed
// as 'native' to multi-country regions.
/////////////////////////////////////////////////////

echo "Inserting implied absences due to endemism in region:\r\n";

// Get regions which are NOT single countries
$sql_region="
SELECT region
FROM fwi_regions_raw
WHERE is_country<>1 
AND region NOT IN ('hispaniola','virginIslands')
;
";
$regions = mysql_query($sql_region);

// Process each region, inserting only absences
while ($row = mysql_fetch_assoc($regions)) {	
	$region = $row["region"];
	echo "  $region...";
		
	$sql="
	INSERT INTO fwi_raw_final (
	source_name,
	country,
	state_province,
	county_parish,
	family,
	genus,
	species,
	taxon,
	taxon_rank,
	native_status,
	native_status_details,
	cult_status
	)
	SELECT
	CONCAT('$src',' (endemic to region ','$region', ')'),
	b.country,
	NULL,
	NULL,
	family,
	genus,
	species,
	taxon,
	taxon_rank,
	'absent',
	'Endemic elsewhere in region $region',
	NULL
	FROM fwi_raw_temp a, country b
	LEFT JOIN fwi_region_country c
	ON b.country=c.country
	WHERE b.country NOT IN ($cclist_countries)
	AND a.native_status='endemic'
	AND a.region='$region'
	AND c.country IS NULL
	;
	";
	sql_execute_multiple($sql);	
	echo $done;
}

?>