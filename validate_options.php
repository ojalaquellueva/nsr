<?php

//////////////////////////////////////////////
// Validate options passed to API
//
// Note that if multiple errors detected, only
// the last gets reported
//////////////////////////////////////////////

// Sources
// NOT YET USED
if (array_key_exists('sources', $opt_arr)) {
	$sources = $opt_arr['sources'];
	
	if ( trim($sources) == "" ) {
		$sources = $NSR_DEF_SOURCES;
	} else {
		$src_arr = explode(",",$sources);
		$valid = count(array_intersect($src_arr, $NSR_SOURCES)) == count($src_arr);
		if ( $valid === false ) {
			$err_msg="ERROR: Invalid option '$sources' for 'sources'\r\n"; 
			$err_code=400; $err=true;
		}
	}
} else {
	$sources = $NSR_DEF_SOURCES;
}


// Processing mode
if (array_key_exists('mode', $opt_arr)) {
	$mode = $opt_arr['mode'];
	
	if ( trim($mode) == "" ) {
		$mode = $NSR_DEF_MODE;
	} else {
		$valid = in_array($mode, $NSR_MODES);
		if ( $valid === false ) {
			$err_msg="ERROR: Invalid option '$mode' for 'mode'\r\n"; 
			$err_code=400; $err=true;
		}
	}
} else {
	$mode = $NSR_DEF_MODE;
}

?>