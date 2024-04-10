<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
///////////////////////////////////////////////////////

echo "Loading checklist metadata to table poldiv_source_staging:\r\n";

// Converting empty lists into arbitrary non-matching value
// so SQL doesn't fail
if ($cclist_countries=="") {
	$cclist_countries_inlist="'arbitrarynonmatchingvalue'";
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
sql_execute_multiple($dbh, $sql);
echo $done;

// Load comprehesive checklist states, if applicablr
if (isset($cclist_states_from_country)) {
	echo "  Loading comprehensive state checklists from list...";
	
	if ($cclist_states_from_country===true) {
		// Extract comprehensive state checklists from country
		$sql="
		INSERT INTO poldiv_source_staging (
		poldiv_id, 
		poldiv_type, 
		source_name, 
		checklist_type,
		checklist_details
		)
		SELECT DISTINCT
		state_province_id, 
		'state_province', 
		'$src', 
		'comprehensive',
		'$source_name_full'
		FROM state_province
		WHERE country IN ($cclist_countries_inlist)
		;
		";
		sql_execute_multiple($dbh, $sql);
		echo $done;
	}
} elseif ( !"$tbl_cclist_states"=="" ) {
	$tbl_cclist_states_expected=$src."_cclist_states";

	if ( exists_table($dbh,"$tbl_cclist_states_expected") ) {
		echo "  Loading comprehensive state checklists from table `$tbl_cclist_states`...";
		$sql="
		INSERT INTO poldiv_source_staging (
		poldiv_id, 
		poldiv_type, 
		source_name, 
		checklist_type,
		checklist_details
		)
		SELECT DISTINCT
		state_province_id, 
		'state_province', 
		'$src', 
		'comprehensive',
		'$source_name_full'
		FROM $tbl_cclist_states
		;
		";
		sql_execute_multiple($dbh, $sql);
		echo $done;
	}
}

?>