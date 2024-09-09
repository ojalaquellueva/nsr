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
sql_execute_multiple($dbh, $sql);
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
sql_execute_multiple($dbh, $sql);
echo $done;

// Drop all indexes, including PKey, on staging table to speed up updates
echo "  Dropping all indexes on staging table...";
$sql="
ALTER TABLE distribution_staging 
DROP INDEX country, 
DROP INDEX county_parish, 
DROP INDEX cult_status, 
DROP INDEX family, 
DROP INDEX genus, 
DROP INDEX native_status, 
DROP INDEX native_status_details, 
DROP INDEX poldiv_full, 
DROP INDEX source_name, 
DROP INDEX species, 
DROP INDEX state_code, 
DROP INDEX state_province, 
DROP INDEX taxon, 
DROP INDEX taxon_rank
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Inserting state observations:\r\n";
// Loop through each state column of raw table
echo "    Processing state column 1 of 32";
// Insert observation for each non-empty state column
// Note that there are 32 state code columns
for ($x = 1; $x <= 32; $x++) {
	$state_col = "state".$x;
	echo "\r    Processing state column $x of 32";
	
	// Insert the state-level observations for this column
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
	SELECT  
	'$src',
	'Mexico',
	TRIM(`$state_col`),
	NULL,
	`taxon`,
	`taxon_rank`,
	'native',
	NULL,
	TRIM(`$state_col`)
	FROM $tbl_raw
	WHERE `$state_col` IS NOT NULL 
	AND NOT `$state_col`='' 
	AND NOT `$state_col`='NA'
	;
	";
	
	// add record to new table
	sql_execute_multiple($dbh, $sql);					
}
echo "\r    Processing state column $x of 32...done\r\n";

echo "  Restoring indexes on staging table...";
$sql="
ALTER TABLE distribution_staging 
ADD INDEX (country), 
ADD INDEX (county_parish), 
ADD INDEX (cult_status), 
ADD INDEX (family), 
ADD INDEX (genus), 
ADD INDEX (native_status), 
ADD INDEX (native_status_details), 
ADD INDEX (poldiv_full), 
ADD INDEX (source_name), 
ADD INDEX (species), 
ADD INDEX (state_code), 
ADD INDEX (state_province), 
ADD INDEX (taxon), 
ADD INDEX (taxon_rank)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

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
sql_execute_multiple($dbh, $sql);
echo $done;

/* 
Skipping. Best not to flag state endemics given uncertainty.
Set all state level occurrences to 'native' in separate script

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
sql_execute_multiple($dbh, $sql);
echo $done;
*/

echo "  Removing temporary column state_code...";
$sql="
ALTER TABLE distribution_staging 
DROP COLUMN state_code 
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>