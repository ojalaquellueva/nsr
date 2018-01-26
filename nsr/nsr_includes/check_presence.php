<?php

////////////////////////////////////////////////////////////////
// Updates native status of using presence in regional
// checklist. 
//
// Separate queries are performed for each of the three
// political divisions. Whether status is inherited at
// higher or lower political divisions differs among different
// statuses. 
////////////////////////////////////////////////////////////////

if ($echo_on) echo "  Checking presence...";

// First, add another index, needed below
$sql="
ALTER TABLE observation
ADD INDEX(native_status);
";
sql_execute_multiple($sql);	

//echo "Updating status using species presence in checklists:\r\n";

//echo "  Presence-only (no status)...";
// One query for each of the 3 political divisions
// Inherited upwards
$sql="
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.county_parish_full=d.county_parish_full
SET 
o.native_status_country='P',
o.native_status_state_province='P',
o.native_status_county_parish='P'
WHERE o.county_parish IS NOT NULL AND d.county_parish IS NOT NULL
AND d.native_status='unknown'
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.state_province_full=d.state_province_full
SET 
o.native_status_country='P',
o.native_status_state_province='P'
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND d.native_status='unknown'
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
SET 
o.native_status_country='P'
WHERE 
d.native_status='unknown'
AND $CACHE_WHERE
;
";
sql_execute_multiple($sql);	


// echo "  Introduced status based on endemism elsewhere:\r\n";
// Inherited downwards
// Replaces previous designations of present, but can be 
// over-ridden later if checklist asserts species is native

//echo "    Endemic species...";
$sql="
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.state_province_full=d.state_province_full
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ne',
o.native_status_county_parish='Ie'
WHERE o.county_parish IS NOT NULL AND d.county_parish IS NOT NULL
AND d.native_status='endemic'
AND o.county_parish<>d.county_parish
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ie',
o.native_status_county_parish=if(o.county_parish IS NULL, 'Ie', NULL)
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND d.native_status='endemic'
AND o.state_province<>d.state_province
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.species=d.taxon
SET 
o.native_status_country='Ie',
o.native_status_state_province=IF(o.state_province IS NOT NULL, 'Ie', NULL),
o.native_status_county_parish=if(o.county_parish IS NOT NULL, 'Ie', NULL)
WHERE 
d.native_status='endemic'
AND o.country<>d.country
AND $CACHE_WHERE
;
";
sql_execute_multiple($sql);	

//echo "    Endemic genera...";
$sql="
UPDATE observation o JOIN distribution d
ON o.genus=d.taxon
AND o.state_province_full=d.state_province_full
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ne',
o.native_status_county_parish='Ie'
WHERE o.county_parish IS NOT NULL AND d.county_parish IS NOT NULL
AND d.native_status='endemic'
AND o.county_parish<>d.county_parish
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.genus=d.taxon
AND o.country=d.country
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ie',
o.native_status_county_parish=if(o.county_parish IS NULL, 'Ie', NULL)
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND d.native_status='endemic'
AND o.state_province<>d.state_province
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.genus=d.taxon
SET 
o.native_status_country='Ie',
o.native_status_state_province=IF(o.state_province IS NOT NULL, 'Ie', NULL),
o.native_status_county_parish=if(o.county_parish IS NOT NULL, 'Ie', NULL)
WHERE 
d.native_status='endemic'
AND o.country<>d.country
AND $CACHE_WHERE
;
";
sql_execute_multiple($sql);	

//echo "    Endemic families...";
$sql="
UPDATE observation o JOIN distribution d
ON o.family=d.taxon
AND o.state_province_full=d.state_province_full
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ne',
o.native_status_county_parish='Ie'
WHERE o.county_parish IS NOT NULL AND d.county_parish IS NOT NULL
AND d.native_status='endemic'
AND o.county_parish<>d.county_parish
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.family=d.taxon
AND o.country=d.country
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ie',
o.native_status_county_parish=if(o.county_parish IS NULL, 'Ie', NULL)
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND d.native_status='endemic'
AND o.state_province<>d.state_province
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.family=d.taxon
SET 
o.native_status_country='Ie',
o.native_status_state_province=IF(o.state_province IS NOT NULL, 'Ie', NULL),
o.native_status_county_parish=if(o.county_parish IS NOT NULL, 'Ie', NULL)
WHERE 
d.native_status='endemic'
AND o.country<>d.country
AND $CACHE_WHERE
;
";
sql_execute_multiple($sql);	

//echo "  Native species...";
// Inherited upwards
// Replaces present
$sql="
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.county_parish_full=d.county_parish_full
SET 
o.native_status_country='N',
o.native_status_state_province='N',
o.native_status_county_parish='N'
WHERE o.county_parish IS NOT NULL AND d.county_parish IS NOT NULL
AND d.native_status='native'
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.state_province_full=d.state_province_full
SET 
o.native_status_country='N',
o.native_status_state_province='N'
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND d.native_status='native'
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
SET 
o.native_status_country='N'
WHERE 
d.native_status='native'
AND $CACHE_WHERE
;

";
sql_execute_multiple($sql);	

//echo "  Endemic taxa:\r\n";
// Inherited upwards.
// Replaces present, native, introduced.
// Doesn't try to resolve conflicts between lists, simply
// treats conflicting status applied earlier in this
// sequence as incomplete or wrong.

//echo "    Species...";
$sql="
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.county_parish_full=d.county_parish_full
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ne',
o.native_status_county_parish='Ne'
WHERE o.county_parish IS NOT NULL AND d.county_parish IS NOT NULL
AND d.native_status='endemic'
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.state_province_full=d.state_province_full
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ne'
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND d.native_status='endemic'
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
SET 
o.native_status_country='Ne'
WHERE 
d.native_status='endemic'
AND $CACHE_WHERE
;
";
sql_execute_multiple($sql);	

//echo "    Genera...";
$sql="
UPDATE observation o JOIN distribution d
ON o.genus=d.taxon
AND o.county_parish_full=d.county_parish_full
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ne',
o.native_status_county_parish='Ne'
WHERE o.county_parish IS NOT NULL AND d.county_parish IS NOT NULL
AND d.native_status='endemic'
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.genus=d.taxon
AND o.state_province_full=d.state_province_full
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ne'
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND d.native_status='endemic'
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.genus=d.taxon
AND o.country=d.country
SET 
o.native_status_country='Ne'
WHERE 
d.native_status='endemic'
AND $CACHE_WHERE
;
";
sql_execute_multiple($sql);	

//echo "    Families...";
$sql="
UPDATE observation o JOIN distribution d
ON o.family=d.taxon
AND o.county_parish_full=d.county_parish_full
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ne',
o.native_status_county_parish='Ne'
WHERE o.county_parish IS NOT NULL AND d.county_parish IS NOT NULL
AND d.native_status='endemic'
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.family=d.taxon
AND o.state_province_full=d.state_province_full
SET 
o.native_status_country='Ne',
o.native_status_state_province='Ne'
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND d.native_status='endemic'
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.family=d.taxon
AND o.country=d.country
SET 
o.native_status_country='Ne'
WHERE 
d.native_status='endemic'
AND $CACHE_WHERE
";
sql_execute_multiple($sql);	

//echo "  Introduced species...";
// Inherited downwards
// Replaces present, native, endemic 
// Doesn't attempt to resolve conflicting status
// designations, simply changes them. Thus, 
// automatically prefers a designation of introduced 
// over a designation of native or endemic.
// For previous designations of "Ie" (endemism inferred
// based on endemism elsewhere) refineds to "I" (meaning
// definitely known as introduced for this region

$sql="
UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.country=d.country
SET 
o.native_status_country='I',
o.native_status_state_province=IF(o.state_province IS NOT NULL, 'I',NULL),
o.native_status_county_parish=IF(o.county_parish IS NOT NULL, 'I', NULL)
WHERE 
d.native_status IN ('introduced','non-native','not native')
AND d.state_province_full IS NULL
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.state_province_full=d.state_province_full
SET 
o.native_status_state_province='I',
o.native_status_county_parish=IF(o.county_parish IS NOT NULL, 'I', NULL)
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND d.native_status IN ('introduced','non-native','not native')
AND d.county_parish IS NULL
AND $CACHE_WHERE
;

UPDATE observation o JOIN distribution d
ON o.species=d.taxon
AND o.county_parish_full=d.county_parish_full
SET 
o.native_status_county_parish='I'
WHERE o.county_parish IS NOT NULL AND d.county_parish IS NOT NULL
AND d.native_status IN ('introduced','non-native','not native')
AND d.county_parish IS NULL
AND $CACHE_WHERE
;
";
sql_execute_multiple($sql);	

// Special updates for USDA Plants checklist 
// Allows UPWARD inheritance of introduced status 
// for state or province level records, but for Canada and
// Lower 48 states only. For these states/province, 
// introduced status is only assigned at 
// state/province level by inheritance from country level,
// so we automatically know that species is introduced
// at country level as well
$special_where = "
source_name='usda' AND (d.country='Canada' OR (d.country='United States' 
AND d.state_province NOT IN ('Alaska','Hawaii','Puerto Rico','Virgin Islands') ) )
";

$sql="
UPDATE observation o JOIN distribution d JOIN source s
ON o.species=d.taxon AND o.country=d.country AND d.source_id=s.source_id
SET 
o.native_status_country='I',
o.native_status_state_province=IF(o.state_province IS NOT NULL, 'I',NULL),
o.native_status_county_parish=IF(o.county_parish IS NOT NULL, 'I', NULL)
WHERE 
d.native_status IN ('introduced','non-native','not native')
AND d.state_province IS NULL
AND d.county_parish IS NULL
AND $CACHE_WHERE 
AND $special_where
;

UPDATE observation o JOIN distribution d JOIN source s
ON o.species=d.taxon
AND o.state_province_full=d.state_province_full
AND d.source_id=s.source_id
SET 
o.native_status_country='I',
o.native_status_state_province='I',
o.native_status_county_parish=IF(o.county_parish IS NOT NULL, 'I', NULL)
WHERE o.state_province IS NOT NULL AND d.state_province IS NOT NULL
AND d.native_status IN ('introduced','non-native','not native')
AND d.county_parish IS NULL
AND $CACHE_WHERE
AND $special_where
;

";
sql_execute_multiple($sql);	
if ($echo_on) echo "done\r\n";

?>