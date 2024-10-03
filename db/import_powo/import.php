<?php

////////////////////////////////////////////////////
// Imports species distribution data
////////////////////////////////////////////////////

// Parameters specific to this source
include "params.inc";	

////////////// Import raw data //////////////////////
echo "Data path: '" . $datapath . "'\n";

// create empty import table
include "create_raw_data_tables.inc";

// import text files to raw data tables
include "import.inc";

// Combine the raw names and distribution tables
include "combine_raw.inc";

// import text files to raw data tables
include "alter_tables.inc";

echo "Standardizing `$tbl_raw`:\n";

// import text files to raw data tables
include "update_native_status.inc";

// Remove rows not usable by NSR
include "delete_bad_rows1.inc";

// Scrub regions with GNRS API
include "scrub_regions.inc";

// Remove rows not usable by NSR
include "delete_bad_rows2.inc";

// separate taxon name from author and dump to taxon field
include "standardize_rank.inc";

// Mark duplicate taxon+poldiv combos for removal
include "mark_duplicates.inc";

// load data from combined raw data table to standardized staging table
include "create_distribution_staging.inc";
include "load_staging.inc";
if ($citation_from_bibtex) include "load_source_citation_staging.inc";

// load metadata on regions covered by this source
include "prepare_cclist_countries.inc";
include "prepare_cclist_states.inc";
include "create_poldiv_source_staging.inc";
include "load_poldiv_source_staging.inc"; 

// delete raw data tables
if ($drop_raw || $drop_raw_force) {
	include "cleanup.inc";
}

//////////////////////////////////////////////////////////


?>