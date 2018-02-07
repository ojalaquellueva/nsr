<?php
// Imports species distribution data from souce fwi

include "params.inc";	// source-specific parameters

//////////////////////////////////////////
// Import raw data file 
//////////////////////////////////////////

// create empty import table
// These must be identical in structure to raw data file
include "create_raw_data_tables.inc";

// import raw data file
include "import.inc";

//////////////////////////////////////////
// Standardize and normalize 
//////////////////////////////////////////

echo "Standardizing $tbl_raw:\r\n";

// Add any extra columns and indexes needed
include "alter_tbl_raw.inc";

// Make fixes specific to this source, if any
include "source_specific_fixes.inc";

/* Not needed for this source

// standardize hybrid x to plain ascii
include "fix_hybrid_x.inc";

// separate taxon name from author and dump to taxon field
include "detect_rank.inc";	

// Normalize the raw data
include "normalize_regions.inc";

// Normalize the raw data
include "normalize_occurrences.inc";
*/	

// standardize status codes
include "standardize_status.inc";

// Insert unique values into temp table & rename to main table
include "unique_occurrences.inc";

/* Not needed for this source
// Insert the occurrences
include "insert_country_occurrences.inc";
include "insert_explicit_absent_introduced.inc";
*/

/* Skip this! Algorithm handles endemics automatically
include "insert_implied_absences.inc";
*/
//////////////////////////////////////////
// Load to staging tables 
//////////////////////////////////////////

// load data from combined raw data table to standardized staging table
include "create_distribution_staging.inc";
include "load_distribution_staging.inc";

// load metadata on regions covered by this source
include "create_poldiv_source_staging.inc";
include "load_poldiv_source_staging.inc";

//exit("\r\nExiting...");
// delete temporary tables, if any

if ($drop_raw || $drop_raw_force) {
	include "cleanup.inc";
}

?>