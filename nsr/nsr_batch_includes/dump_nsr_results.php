<?php

//////////////////////////////////////////////////////
// Dump the records for this job from table observation 
// to results file in data directory
//////////////////////////////////////////////////////

include "dbw_open.php";

if ($echo_on) echo "Saving results to '$resultsfile'...";

$cmd="mysql -u $USERW --password=$PWDW -B $DB_BATCH -e \"select id, job, family, genus, species, country, state_province, state_province_full, county_parish, county_parish_full, poldiv_full, poldiv_type, native_status_country, native_status_state_province, native_status_county_parish, native_status, native_status_reason, native_status_sources, isIntroduced, isCultivatedNSR, is_cultivated_taxon, user_id from observation where $JOB_WHERE_NA \" > $resultsfile";
//echo "cmd:\n$cmd\n";
exec($cmd);
if ($echo_on) echo $done;

if ($echo_on) echo "Converting NULLs to blanks...";
$cmd="sed -i 's/NULL//g' $resultsfile";
exec($cmd);
if ($echo_on) echo $done;

include "db_close.php";

?>