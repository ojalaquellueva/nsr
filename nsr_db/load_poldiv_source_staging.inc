<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
///////////////////////////////////////////////////////

echo "Loading checklist metadata to table poldiv_source_staging:\r\n";

// Converting empty lists into arbitrary non-matching value
// so SQL doesn't fail
if ($cclist_countries=="") {
	$cclist_countries_inlist="12345";
} else {
	$cclist_countries_inlist=$cclist_countries;
}

/* Not needed unless activate rest of script
// Will need to ensure parameter $pclist_countries is
// present in each source, or check isset()
if ($pclist_countries=="") {
	$pclist_countries_inlist="12345";
} 
*/

// Comprehensive country checklists are critical
// For these lists, absence counts as introduced
echo "  Loading comprehensive country checklists...";
$sql="
INSERT INTO poldiv_source_staging (
poldiv_id, 
poldiv_type, 
source_name, 
checklist_type,
checklist_details
)
SELECT DISTINCT
country_id, 
'country', 
'$src', 
'comprehensive',
'$source_name_full'
FROM country
WHERE country IN ($cclist_countries_inlist)
;
";
sql_execute_multiple($sql);
echo $done;

/* Omit other lists for now. 
// Fragile code will take too long to fix
// Changes needed to activate: 
// 1. For each source, must set variable $tbl_raw_final to
// whatever table is loaded to staging
// 2. $tbl_raw_final MUST contain column inferred, with default=0
echo "  Loading explicit partial country checklists...";
$sql="
INSERT INTO poldiv_source_staging (
poldiv_id, 
poldiv_type, 
source_name, 
checklist_type,
checklist_details
)
SELECT DISTINCT
a.country_id, 
'country', 
'$src', 
'partial',
'$source_name_full'
FROM country a JOIN $tbl_raw b 
ON a.country=b.country
WHERE a.country NOT IN ($cclist_countries_inlist)
AND inferred=0
;
";
sql_execute_multiple($sql);
echo $done;


echo "  Loading inferred-by-endemisim partial country checklists...";
$sql="
INSERT INTO poldiv_source_staging (
poldiv_id, 
poldiv_type, 
source_name, 
checklist_type,
checklist_details
)
SELECT DISTINCT
a.country_id, 
'country', 
'$src', 
'partial',
'Introduced species inferred from endemics in source $src'
FROM country a JOIN $tbl_raw b 
ON a.country=b.country
WHERE a.country NOT IN ($cclist_countries_inlist)
AND a.country NOT IN ($pclist_countries_inlist)
AND inferred=1
;
";
sql_execute_multiple($sql);
echo $done;
*/

?>