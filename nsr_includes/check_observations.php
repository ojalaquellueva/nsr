<?php

// UNDER DEVELOPMENT!

////////////////////////////////////////////////////////////////
// For each species observation in table observation, checks 
// native and cultivated status within each declared political
// division. 
////////////////////////////////////////////////////////////////

$poldiv_arr=array(
	'country',
	'state_province',
	'county_parish'
);

// Begin by marking "not in list" for all observations with political
// division represented in one or more comprehensive checklists.
// This value will later be written over for species which are in 
// checklist.
echo "Marking species absent from comprehensive regional lists...";
// Do for each of the three political divisions
foreach ($poldiv_arr as $poldiv) {
	//echo "  $poldiv...";
	if ($poldiv=='country') {
		$poldiv_select = "country";
		$poldiv_on = "o.country=d.country";		
	} elseif ($poldiv=='state_province') {
		$poldiv_select = "country, state_province";
		$poldiv_on = "o.country=d.country 
		AND o.state_province=d.state_province";	
	} else {
		// $poldiv='county_parish'
		$poldiv_select = "country, state_province, county_parish";
		$poldiv_on = "o.country=d.country 
		AND o.state_province=d.state_province
		AND o.county_parish=d.county_parish";	
	}

	// Form the appropriate SQL and execute it
	$sql="
		UPDATE observation o JOIN 
		(
		SELECT DISTINCT ".$poldiv_select."
		FROM distribution d JOIN source s
		ON d.source_id=s.source_id
		WHERE is_comprehensive=1
		) AS d
		ON ".$poldiv_on."
		SET o.native_status_".$poldiv."='not in list',
		o.cult_status_".$poldiv."='not in list'
		;	
	";
	sql_execute_multiple($dbh, $sql);	
	//echo $done;
} 
echo $done;

// For each species update status for each of the three political divisions
// for which distribution information is available
// WARNING: beta version. Does NOT support multiple opinions per species
// per political division (will use only one if >1 opinion)
echo "Finding distribution records within each political division...";
// Do for each of the three political divisionsforeach ($poldiv_arr as $poldiv) {
foreach ($poldiv_arr as $poldiv) {
	if ($poldiv=='country') {
		$poldiv_select = "country";
		$poldiv_on = "o.country=d.country";		
	} elseif ($poldiv=='state_province') {
		$poldiv_select = "country, state_province";
		$poldiv_on = "o.country=d.country 
		AND o.state_province=d.state_province";	
	} else {
		// $poldiv='county_parish'
		$poldiv_select = "country, state_province, county_parish";
		$poldiv_on = "o.country=d.country 
		AND o.state_province=d.state_province
		AND o.county_parish=d.county_parish";	
	}

	// Form the appropriate SQL and execute it
	$sql="
		UPDATE observation o JOIN 
		(
		SELECT DISTINCT taxon, native_status, cult_status, ".$poldiv_select."
		FROM distribution d JOIN source s
		ON d.source_id=s.source_id
		WHERE is_comprehensive=1
		) AS d
		ON o.species=d.taxon 
		AND ".$poldiv_on."
		SET o.native_status_".$poldiv."=d.native_status,
		o.cult_status_".$poldiv."=d.cult_status
		;	
	";
	sql_execute_multiple($dbh, $sql);	
} 
echo $done;

// Mark as introduced any species listed as endemic to other regions, as
// long as those species not already makred as native
echo "Marking introduced species listed as endemic to other political divisions...";
// Do for each of the three political divisionsforeach ($poldiv_arr as $poldiv) {
foreach ($poldiv_arr as $poldiv) {
	if ($poldiv=='country') {
		$poldiv_select = "country";
		$poldiv_where = "o.country<>d.country";		
	} elseif ($poldiv=='state_province') {
		$poldiv_select = "country, state_province";
		$poldiv_where = "o.country<>d.country 
		AND o.state_province<>d.state_province";	
	} else {
		// $poldiv='county_parish'
		$poldiv_select = "country, state_province, county_parish";
		$poldiv_where = "o.country<>d.country 
		AND o.state_province<>d.state_province
		AND o.county_parish<>d.county_parish";	
	}

	// Form the appropriate SQL and execute it
	$sql="
		UPDATE observation o JOIN 
		(
		SELECT DISTINCT taxon, native_status, cult_status, ".$poldiv_select."
		FROM distribution d JOIN source s
		ON d.source_id=s.source_id
		WHERE is_comprehensive=1
		) AS d
		ON o.species=d.taxon 
		SET o.native_status_".$poldiv."='non-native (ENDEMIC ELSEWHERE)',
		o.cult_status_".$poldiv."='unknown'
		WHERE d.native_status='endemic'
		AND $poldiv_where
		;	
	";
	sql_execute_multiple($dbh, $sql);	
} 
echo $done;




?>