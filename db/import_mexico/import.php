<?php
// Imports species distribution data from source USDA Plants

include "params.inc";	// everything you need to set is here and in global_params.inc

////////////// Import raw data //////////////////////
echo "Data path: '" . $datapath . "'\n";

// create empty import table
// These must be identical in structure to raw data file
include "create_raw_data_tables.inc";

// import raw data file
include "import.inc";

echo "Standardizing $tbl_raw:\r\n";

// Add any extra columns and indexes needed
include "alter_raw.inc";

// Make fixes specific to this source, if any
include "source_specific_fixes.inc";

// standardize hybrid x to plain ascii
include "fix_hybrid_x.inc";

// separate taxon name from author and dump to taxon field
include "detect_rank.inc";

// load data from combined raw data table to standardized staging table
include "create_distribution_staging.inc";
//include "load_staging.inc";
include "load_staging_alt.inc";
if ($citation_from_bibtex) include "load_source_citation_staging.inc";

// Fix source-specific issue: change native_status for state-
// level occurrences from 'endemic' to 'native'
include "fix_state_occurrences.inc";

// load metadata on regions covered by this source
include "create_poldiv_source_staging.inc";
include "load_poldiv_source_staging.inc"; // NOT READY

// delete temporary tables, if any
if ($drop_raw || $drop_raw_force) {
	include "cleanup.inc";
}

//////////////////////////////////////////////////////////

?>