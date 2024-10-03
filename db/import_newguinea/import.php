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

// Insert country- and state-level observations to new table
include "load_raw_final.inc";

echo "Standardizing " . $src . "_raw:\r\n";

// separate taxon name from author and dump to taxon field
include "infer_rank.inc";

// separate taxon name from author and dump to taxon field
include "standardize_rank.inc";

// import text files to raw data tables
include "index_tables.inc";

// load data from combined raw data table to standardized staging table
include "create_distribution_staging.inc";
include "load_staging.inc";
if ($citation_from_bibtex) include "load_source_citation_staging.inc";

// load metadata on regions covered by this source
include "prepare_cclist_states.inc";
include "create_poldiv_source_staging.inc";
include "load_poldiv_source_staging.inc"; 

// delete raw data tables
if ($drop_raw || $drop_raw_force) {
	include "cleanup.inc";
}

//////////////////////////////////////////////////////////


?>