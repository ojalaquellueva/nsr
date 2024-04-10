<?php

////////////////////////////////////////////////////
// Imports species distribution data
////////////////////////////////////////////////////

// Parameters specific to this source
include "params.inc";	

/* 
// For development only
echo "WARNING: sections of import_powo/import.php commented out!\n";
echo "Correct before production run!!!\n\n";
$tbl_region_codes=$src."_region_codes";
$tbl_poldivs = $src . "_poldivs";
$tbl_poldivs_scrubbed = $src . "_poldivs_gnrs";
//  END For development only
 */


////////////// Import raw data file //////////////////////

// create empty import table
include "create_raw_data_tables.inc";

// import text files to raw data tables
include "import.inc";

// import text files to raw data tables
include "alter_tables.inc";

echo "Standardizing " . $src . "_raw:\r\n";

// Remove rows not relevant to NSR
include "delete_unnecessary_rows.inc";

// separate taxon name from author and dump to taxon field
include "standardize_rank.inc";

// standardize native status codes
include "standardize_status.inc";

// Scrub regions with GNRS API
include "scrub_regions.inc";

// Mark duplicate taxon+poldiv combos for removal
include "mark_duplicates.inc";

// load data from combined raw data table to standardized staging table
include "create_distribution_staging.inc";
include "load_staging.inc";

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