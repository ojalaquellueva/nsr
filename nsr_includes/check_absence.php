<?php

////////////////////////////////////////////////////////////////
// Updates native status based on absence from *comprehensive*
// regions checklists. Absence is a weak way of inferring that
// a species is introduced. Absent species are merely marked
// "A" (Absent). It is up to the user to decide whether to 
// interpret absence as an indication of introduced status. 
// 
// The approach here is, for every observation, mark status
// as "A" for each political division represented in one
// in one or more comprehensive lists. For species actually
// present in those lists, the "A"s are replaced by actual
// status values in the later "presence" queries. Thus, after
// all steps have been completed, only political divisions
// from which the species is absent remain labeled as "A". 
//
// Unlike "native" or "introduced", absence can only
// be interpreted at the politicial division level to
// which the list applies. A country level checklist
// provides not useable absence level at the state level.
// And a state checklist cannot be use to infer
// absence at the country level
//
// WHERE criteria ensure that the distribution records
// are for the same politicial division represented in 
// the JOIN clause. This prevents, for example, a comprehensive
// state list from being treated as a comprehensive country
// list by matching to the country column but not the 
// state column
// 
// Presence-based inference is handled as a later step by a 
// separate script.
////////////////////////////////////////////////////////////////

if ($echo_on) echo "  Checking absence...";

///////////////////////////////////////////////////
// Mark all political divisions in observation
// table covered by comprehensive lists
///////////////////////////////////////////////////
$sql="
UPDATE observation o JOIN cclist d
ON o.country=d.country
SET 
o.native_status_country='A'
WHERE 
d.state_province IS NULL
AND d.county_parish IS NULL
AND $JOB_WHERE AND $BATCH_WHERE
AND $CACHE_WHERE
;
";
sql_execute_multiple($sql);	

$sql="
UPDATE observation o JOIN cclist d
ON o.country=d.country
AND o.state_province=d.state_province
SET 
o.native_status_state_province='A'
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND d.county_parish IS NULL
AND $JOB_WHERE AND $BATCH_WHERE
AND $CACHE_WHERE
;
";
sql_execute_multiple($sql);	

$sql="
UPDATE observation o JOIN cclist d
ON o.country=d.country
AND o.state_province=d.state_province
AND o.county_parish=d.county_parish
SET 
o.native_status_county_parish='A'
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND o.county_parish IS NOT NULL AND d.county_parish IS NOT NULL
AND $JOB_WHERE AND $BATCH_WHERE
AND $CACHE_WHERE
;
";
sql_execute_multiple($sql);	

if ($echo_on) echo "done\r\n";

?>