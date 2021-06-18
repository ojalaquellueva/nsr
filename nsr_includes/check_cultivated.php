<?php

////////////////////////////////$CACHE_WHERE////////////////////////////////
// Updates is_cultivated_taxon
//
// is_cultivated_taxon:
// Sets is_cultivated_taxon=1 if the taxon is listed as 
// generally cultivated. Does not necessarily mean that the 
// individual plant is cultivated, although likely. It's up
// to the user to decide how to handle observation of taxa
// which are exclusively or widely cultivated
//
// isCultivatedNSR (BIEN: aliased as is_cultivated_in_region):
// Set isCultivatedNSR=1 if taxon is flagged as known to be 
// cultivated in one or more checklist regions.
////////////////////////////////////////////////////////////////

if ($echo_on) echo "  Checking cultivated taxa...";

$sql="
UPDATE observation o JOIN cultspp c
ON o.species=c.taxon
SET o.is_cultivated_taxon=1
WHERE $JOB_WHERE AND $BATCH_WHERE
;
";
sql_execute_multiple($dbh, $sql);	

if ($echo_on) echo "done\r\n";

if ($echo_on) echo "  Checking cultivated in region...";

$sql="
-- county
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
AND o.county_parish=d.county_parish
SET o.isCultivatedNSR=1
WHERE $JOB_WHERE AND $BATCH_WHERE
AND d.cult_status='cultivated'
;

-- state
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
AND o.state_province=d.state_province
SET o.isCultivatedNSR=1
WHERE $JOB_WHERE AND $BATCH_WHERE
AND d.cult_status='cultivated'
;

-- country
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
SET o.isCultivatedNSR=1
WHERE $JOB_WHERE AND $BATCH_WHERE
AND d.cult_status='cultivated'
;
";
sql_execute_multiple($dbh, $sql);	

if ($echo_on) echo "done\r\n";

?>