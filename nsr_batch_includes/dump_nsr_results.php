<?php

//////////////////////////////////////////////////////
// Dump the records for this job from table observation 
// to results file in data directory
//////////////////////////////////////////////////////

include "dbw_open.php";

if ($echo_on) echo "Exporting results to '$resultsfile'...";

/*
This method now throws the following warning:
mysql: [Warning] Using a password on the command line interface can be insecure.
However, better than the granting FILE permission.
For possible solutions, see:
https://stackoverflow.com/questions/20751352/suppress-warning-messages-using-mysql-from-within-terminal-but-password-written
*/
$cmd="mysql -u $USERW --password=$PWDW -B $DB_BATCH -e \"select id, family, IF(genus LIKE '%aceae','',genus) AS genus, IF(species NOT LIKE '% %','',species) AS species, country, IFNULL(state_province,'') AS state_province, IFNULL(county_parish,'') AS county_parish, poldiv_full, poldiv_type, native_status_country, native_status_state_province, native_status_county_parish, native_status, native_status_reason, native_status_sources, isIntroduced, isCultivatedNSR, is_cultivated_taxon, user_id from observation where $JOB_WHERE_NA \" > $resultsfile";
//echo "cmd:\n$cmd\n";
exec($cmd);

/*
// The following requires FILE permission by the user, which may
// be insecure
$sql="
select id, job, family, genus, species, country, state_province, state_province_full, county_parish, county_parish_full, poldiv_full, poldiv_type, native_status_country, native_status_state_province, native_status_county_parish, native_status, native_status_reason, native_status_sources, isIntroduced, isCultivatedNSR, is_cultivated_taxon, user_id from observation where $JOB_WHERE_NA
INTO OUTFILE '$resultsfile'
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
;
";
sql_execute_multiple($dbh, $sql);
*/

// Convert NULLs to blanks...";
$cmd="sed -i 's/NULL//g' $resultsfile";
exec($cmd);
if ($echo_on) echo $done;

include "db_close.php";

?>