<?php

//////////////////////////////////////////////////////
// Dump the records for this job from table observation 
// to results file in data directory
//////////////////////////////////////////////////////

include "dbw_open.php";

if ($echo_on) echo "Exporting results to '$resultsfile'...";

$cmd="export MYSQL_PWD=$PWDW; mysql -u $USERW -B $DB_BATCH -e \"select id, IFNULL(family,'') AS family, IFNULL(IF(genus LIKE '%aceae','',genus),'') AS genus, IFNULL(IF(species NOT LIKE '% %','',species),'') AS species, country, IFNULL(state_province,'') AS state_province, IFNULL(county_parish,'') AS county_parish, poldiv_full, poldiv_type, native_status_country, native_status_state_province, native_status_county_parish, IFNULL(native_status,'') AS native_status, IFNULL(native_status_reason,'') AS native_status_reason, IFNULL(native_status_sources,'') AS native_status_sources, isIntroduced, isCultivatedNSR, is_cultivated_taxon, IFNULL(user_id,'') AS user_id from observation where $JOB_WHERE_NA \" > $resultsfile";
//echo "cmd:\n$cmd\n";
exec($cmd);

// Convert NULLs to blanks...";
$cmd="sed -i 's/NULL//g' $resultsfile";
exec($cmd);
if ($echo_on) echo $done;

include "db_close.php";

?>