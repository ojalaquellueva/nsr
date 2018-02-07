<?php

/////////////////////////////////////////////////////////////
// Loads staging table to core database
/////////////////////////////////////////////////////////////

echo "Loading staging table to core db:\r\n";

// Update source information and get sourceID (needed for later steps)
include 'load_source.inc';

// Load metadata on checklists
include 'load_poldiv_source.inc';

// Load metadata on comprehensive checklists
include 'load_cclist.inc';

// Delete previous records
// Tag records linked ONLY to current source, then delete those records
if ($replace===true) {
	include "clear_previous.inc";
}

// Load distribution table
include 'load_distribution.inc';

// Load cultspp table, if this data present
if (exists_table('cultspp_staging')) {
	include 'load_cultspp.inc';
}

// standardize status codes one last time (hack)
include 'standardize_status.inc';
include 'standardize_country.inc';

// Remove staging table
if ($drop_raw || $drop_raw_force) {
	include 'cleanup.inc';
}

?>