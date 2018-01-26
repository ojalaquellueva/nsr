<?php

////////////////////////////////////////////////////
// Performs generic operations on distribution
// staging table prior to normalization to
// core db
////////////////////////////////////////////////////

echo "Preparing staging table:\r\n";

// standardize status codes
// this is a hack because not done consistently earlier
include "standardize_status.inc";

// Adds missing (parent) taxon where record for 
// lower taxon is present but higher taxon is not
echo "  Adding missing parent taxa:\r\n";
include "remove_nulls.inc";		// set NULL poldivs to empty strings
include "add_species.inc";
include "add_genus.inc";
include "add_family.inc";
include "restore_nulls.inc";	// restore empty strings to NULL

?>