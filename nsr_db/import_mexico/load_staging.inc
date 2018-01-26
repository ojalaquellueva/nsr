<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
//
// Omits duplicate records of the same value of taxon 
// + country. Adds status codes from the first of a
// set of multiple country+taxon records. Perhaps run
// manual check to make sure this is not a problem.
///////////////////////////////////////////////////////

echo "Loading raw data to staging table distribution_staging:\r\n";

echo "  Adding temporary column state_code to distribution_staging...";
$sql="
ALTER TABLE distribution_staging 
ADD COLUMN state_code VARCHAR(50) DEFAULT NULL,
ADD INDEX (state_code)
;
";
sql_execute_multiple($sql);
echo $done;


echo "  Inserting country observations...";
$sql="
INSERT INTO distribution_staging (
source_name,
country,
state_province,
county_parish,
taxon,
taxon_rank,
native_status,
cult_status
)
SELECT DISTINCT
'$src',
'Mexico',
NULL,
NULL,
taxon,
taxon_rank,
native_status,
NULL
FROM `$tbl_raw`
;
";
sql_execute_multiple($sql);
echo $done;

echo "  Inserting state observations:\r\n";
// Loop through each record of raw table
$sql_native_status="
SELECT *
FROM $tbl_raw;
";

$result = mysql_query($sql_native_status);
$nrows = mysql_num_rows($result);
$curr_row = 1;
echo "    Processing species $curr_row of $nrows";

while ($row = mysql_fetch_assoc($result)) {	
	$taxon = $row["species"];
	$taxon_rank = $row["taxon_rank"];
	echo "\r    Processing species $curr_row of $nrows                           ";

	// Insert observation for each non-empty state column
	// Note that there are 32 state code columns
	for ($x = 1; $x <= 32; $x++) {
		$col = "state".$x;
		//$msg = "col=".$col;
		//echo $msg;
		
		$state_code = trim($row["$col"]);
		//$msg = "state_code=".$state_code;
		//echo $msg;
		
		if (is_null($state_code) || $state_code=="" || $state_code=="NA" ) break;
		
		// Insert the state-level observation
		$sql = "
		INSERT INTO distribution_staging (
		source_name,
		country,
		state_province,
		county_parish,
		taxon,
		taxon_rank,
		native_status,
		cult_status,
		state_code
		)
		VALUES ( 
		'$src',
		'Mexico',
		'$state_code',
		NULL,
		'$taxon',
		'$taxon_rank',
		'native',
		NULL,
		'$state_code'
		)
		;
		";
		
		// add record to new table
		sql_execute_multiple($sql);					
		
	}
	$curr_row++;
}

$curr_row = $curr_row-1;
echo "\r    Processing species $curr_row of $nrows...done\r\n";

echo "  Populating full state name from codes...";
$sql="
UPDATE distribution_staging a JOIN state_province_name b
ON a.state_code=b.state_province_name
SET a.state_province=b.state_province_std
;
-- Specil updates for codes and mixed codes not in reference table
UPDATE distribution_staging
SET state_province=
CASE
WHEN state_province='CDM' THEN 'Ciudad de Mexico'
WHEN state_province='CDMX' THEN 'Ciudad de Mexico'
WHEN state_province='CDMX.DGO' THEN 'Durango'
WHEN state_province='CHIH' THEN 'Chihuahua'
WHEN state_province='MEXOAX' THEN 'Oaxaca'
WHEN state_province='MOR.OAX' THEN 'Oaxaca'
WHEN state_province='QROO' THEN 'Quintana Roo'
WHEN state_province='SON.VER' THEN 'Sonora'
WHEN state_province='TAMS' THEN 'Tamaulipas'
WHEN state_province='VER.ZAC' THEN 'Veracruz'
ELSE state_province
END;
";
sql_execute_multiple($sql);
echo $done;

// The following best done *after* update full state name
echo "  Updating status for state-level endemics...";
$sql="
UPDATE distribution_staging a JOIN (
SELECT taxon, COUNT(DISTINCT state_province) AS states
FROM distribution_staging
WHERE state_province IS NOT NULL
GROUP BY taxon
HAVING states=1 
) AS b
ON a.taxon=b.taxon
SET native_status='endemic'
WHERE a.state_province IS NOT NULL
;
";
sql_execute_multiple($sql);
echo $done;

echo "  Removing temporary column state_code...";
$sql="
ALTER TABLE distribution_staging 
DROP COLUMN state_code 
;
";
sql_execute_multiple($sql);
echo $done;

?>