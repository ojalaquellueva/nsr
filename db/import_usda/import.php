<?php
// Imports species distribution data from source USDA Plants

include "params.inc";	// everything you need to set is here and in global_params.inc



// For development only
echo "WARNING: sections of import_usda/import.php commented out!\n";
exit("Exiting...\n\n");
/*  END For development only



////////////// Import raw data file //////////////////////

// create empty import table
// These must be identical in structure to raw data file
include "create_raw_data_tables.inc";

// import raw data file
include "import.inc";

// unpack raw download into multiple state checklists
include "parse_usda_plants.inc";

echo "Standardizing $tbl_raw:\r\n";

// Add any extra columns and indexes needed
include "alter_tbl_raw.inc";

// Make fixes specific to this source, if any
include "source_specific_fixes.inc";

// standardize hybrid x to plain ascii
include "fix_hybrid_x.inc";

// separate taxon name from author and dump to taxon field
include "detect_rank.inc";

// separate taxon name from author and dump to taxon field
include "parse_taxon_name.inc";

// standardize status codes
include "standardize_status.inc";

// load data from combined raw data table to standardized staging table
include "create_distribution_staging.inc";
include "load_staging.inc";

// load metadata on regions covered by this source
include "create_poldiv_source_staging.inc";
include "load_poldiv_source_staging.inc"; // NOT READY

// delete temporary tables, if any
if ($drop_raw || $drop_raw_force) {
	include "cleanup.inc";
}

//////////////////////////////////////////////////////////


?>
