<?php
// Imports species distribution data from source USDA Plants

include "params.inc";	// everything you need to set is here and in global_params.inc

////////////// Import raw data file //////////////////////

// create empty import table
// These must be identical in structure to raw data file
include "create_raw_data_tables.inc";

// import raw data file
include "import.inc";
include "index_raw.inc";

// Add any extra columns and indexes needed
//include "alter_raw.inc";		// NOT NEEDED

// Load main raw table from separate taxon and distribution tables
include "load_raw.inc";

// Index main raw table
include "index_raw2.inc";

echo "Standardizing $tbl_raw:\r\n";

// Make fixes specific to this source, if any
include "source_specific_fixes.inc";

// standardize hybrid x to plain ascii
include "fix_hybrid_x.inc";

// separate taxon name from author and dump to taxon field
//include "detect_rank.inc";		// NOT NEEDED

// load data from combined raw data table to standardized staging table
include "create_distribution_staging.inc";
include "load_staging.inc";

// load metadata on regions covered by this source
include "prepare_cclist_states.inc";
include "create_poldiv_source_staging.inc";
include "load_poldiv_source_staging.inc"; // NOT READY

// delete temporary tables, if any
if ($drop_raw || $drop_raw_force) {
	include "cleanup.inc";
}

//////////////////////////////////////////////////////////

?>