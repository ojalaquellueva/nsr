<?php

///////////////////////////////////////////////
// Normalizes raw regions lookup table
///////////////////////////////////////////////

echo "Normalizing regions and countries:\r\n";

echo "  Extracting all region-country combinations...";

$sql="
DROP TABLE IF EXISTS rc_temp;
CREATE TABLE rc_temp LIKE fwi_region_country;
ALTER TABLE rc_temp DROP INDEX region_country;
";
sql_execute_multiple($dbh, $sql);

// Loop through each record of raw table
$sql_native_status="
SELECT * FROM fwi_regions_raw;
";
$result = mysqli_query($dbh, $sql_native_status);

while ($row = mysqli_fetch_assoc($result)) {	
	$region = $row["region"];

	// Insert observation for each non-empty country column
	// Note that there are 26 state code columns
	for ($x = 1; $x <= 26; $x++) {
		$col = "country".$x;
		$country = trim($row["$col"] ?? '');
		
		if (is_null($country) || $country=="" ) break;
		
		// Insert region_country combinations
		$sql = "
		INSERT INTO rc_temp (
		region,
		country
		)
		VALUES ( 
		'$region',
		'$country'
		)
		;
		";
		
		// add record to new table
		sql_execute_multiple($dbh, $sql);					
	}
}
echo $done;

echo "  Extracting distinct region-country combinations....";
$sql="
INSERT INTO fwi_region_country SELECT DISTINCT * FROM rc_temp
WHERE country IS NOT NULL;
DROP TABLE rc_temp;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Extracting countries....";
$sql="
INSERT INTO fwi_country (country)
SELECT DISTINCT country 
FROM fwi_region_country
WHERE country IS NOT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>