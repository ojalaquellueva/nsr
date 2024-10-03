<?php
// Imports species distribution data from Tropicos

include "params.inc";	// everything you need to set is here and in global_params.inc

////////////// Import raw data //////////////////////
echo "Data path: '" . $datapath . "'\n";

// create empty import table
include "create_raw_data_tables.inc";

// import text files to raw data tables
include "import.inc";

// combine raw data tables to single table
include "combine_raw.inc";

echo "Standardizing tropicos_raw:\r\n";

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
if ($citation_from_bibtex) include "load_source_citation_staging.inc";

// load metadata on regions covered by this source
include "create_poldiv_source_staging.inc";
include "load_poldiv_source_staging.inc"; 

// delete raw data tables
if ($drop_raw || $drop_raw_force) {
	include "cleanup.inc";
}

//////////////////////////////////////////////////////////


?>
