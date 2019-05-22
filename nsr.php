<?php

///////////////////////////////////////////////
// Evaluates observations against nsr
// database and adds results to cache
// Connection to db must already exist
///////////////////////////////////////////////

include "dbw_open.php";

//////////////////////////////////////////////////////
// Set batch
//////////////////////////////////////////////////////

// Get batch number
$use_batch = false;		// Assume no batching
if (isset($batch)) {	
	// Abort if bad batch # 
	if ( ! is_int( $batch ) ) {
		die("ERROR: batch # must be a positive integer");
	} else {
		$use_batch = true;	// All good, use batching
	}
} 

// Set batch WHERE clause
if ($use_batch==true) {
	$BATCH_WHERE = " o.batch='$batch' ";
	$BATCH_WHERE_NA = " batch='$batch' ";
} else {
	// No batches, just set this clause to always true
	$BATCH_WHERE = " 1 ";
	$BATCH_WHERE_NA = " 1 ";
}

//////////////////////////////////////////////////////
// Process the observations [by batch if specified]
//////////////////////////////////////////////////////

include $nsr_includes_dir."prepare_observations.php";
include $nsr_includes_dir."check_absence.php";
include $nsr_includes_dir."check_presence.php";
include $nsr_includes_dir."check_cultivated.php";
include $nsr_includes_dir."infer_status.php";
include $nsr_includes_dir."append_to_cache.php";

include "db_close.php";

?>