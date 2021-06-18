<?php

if ($echo_on) echo "Inserting observations...";

// Assign dummy batch number if not in batch mode
if (isset($batch)) {
	$curr_batch=$batch;
} else {
	$curr_batch=1;
}

// insert the raw records
// Note that column batch must be left NULL when observations first inserted
// Batch numbers are assigned at time of processing
// Inserting a batch number at this stage will cause entire
// job to be processed as one batch!
$sql="
INSERT INTO observation (
job,
batch,
species,
country,
state_province,
county_parish,
user_id
)
SELECT 
'$job',
NULL,
species,
country,
state_province,
county_parish,
user_id
FROM observation_raw
;
";
sql_execute_multiple($dbh, $sql);

// HACK: Merge Newfoundland and Labrador
$sql="
UPDATE observation
SET state_province='Newfoundland and Labrador'
WHERE country='Canada' 
AND (state_province LIKE '%Newfoundland%' OR state_province LIKE '%Labrador%')
AND $JOB_WHERE_NA
;
";
sql_execute_multiple($dbh, $sql);

// Convert empty strings to null
$sql="
UPDATE observation 
SET state_province=NULL
WHERE state_province=''
AND $JOB_WHERE_NA
;
UPDATE observation 
SET county_parish=NULL
WHERE county_parish=''
AND $JOB_WHERE_NA
;
";
sql_execute_multiple($dbh, $sql);

// Populate the optimization columns
$sql="
UPDATE observation
SET state_province_full=CONCAT_WS(':',
country,state_province
)
WHERE country IS NOT NULL AND state_province IS NOT NULL
AND $JOB_WHERE_NA
;
UPDATE observation
SET county_parish_full=CONCAT_WS(':',
country,state_province,county_parish
)
WHERE country IS NOT NULL 
AND state_province IS NOT NULL
AND county_parish IS NOT NULL
AND $JOB_WHERE_NA
;
UPDATE observation
SET poldiv_full=
CASE
WHEN country IS NOT NULL AND state_province IS NULL THEN country
WHEN state_province IS NOT NULL AND county_parish IS NULL THEN state_province_full
WHEN county_parish IS NOT NULL THEN county_parish_full
ELSE NULL
END
WHERE $JOB_WHERE_NA
;
UPDATE observation
SET poldiv_type=
CASE
WHEN country IS NOT NULL AND state_province IS NULL THEN 'country'
WHEN state_province IS NOT NULL AND county_parish IS NULL THEN 'state_province'
WHEN county_parish IS NOT NULL THEN 'county_parish'
ELSE NULL
END
WHERE $JOB_WHERE_NA
;
";
sql_execute_multiple($dbh, $sql);

// Drop the raw table
$sql="
DROP TABLE IF EXISTS observation_raw;
";
sql_execute_multiple($dbh, $sql);

if ($echo_on) echo "done\r\n";

?>