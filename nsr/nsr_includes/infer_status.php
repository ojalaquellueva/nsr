<?php

// Hard-wired for now, still needs work

if ($echo_on) echo "  Inferring native status...";

//echo "Inferring overall native status...";
$sql="
-- Country-level status
UPDATE observation
SET native_status=
CASE
WHEN native_status_country='A' THEN 'A'
WHEN native_status_country IS NULL THEN 'UNK'
WHEN native_status_country='P' THEN 'P'
ELSE native_status_country
END
WHERE $BATCH_WHERE_NA
AND $CACHE_WHERE_NA
;

-- State/province level status
-- Status at this level trumps status at country level
UPDATE observation
SET native_status=
CASE
WHEN native_status_state_province='A' THEN 'A'
WHEN native_status_state_province='P' THEN 'P'
WHEN native_status_state_province IS NULL THEN 'UNK'
ELSE native_status_state_province
END
WHERE state_province IS NOT NULL
AND native_status_state_province IS NOT NULL
AND $BATCH_WHERE_NA
AND $CACHE_WHERE_NA
;
";
sql_execute_multiple($sql);

//echo "Populating native status source information...";
$sql="

-- Introduced due to endemism elsewhere
UPDATE observation o JOIN endemic_taxon_sources a
ON o.species=a.taxon
SET 
o.native_status_reason='Introduced, species endemic to other region',
o.native_status_sources=a.sources
WHERE o.native_status='Ie'
AND $CACHE_WHERE
;

-- Introduced
UPDATE observation o JOIN taxon_country_sources a
ON o.species=a.taxon AND o.country=a.country
SET 
o.native_status_reason='Introduced to region, as per checklist',
o.native_status_sources=a.sources
WHERE o.native_status='I' AND a.native_status='introduced'
AND o.native_status_reason IS NULL
AND $CACHE_WHERE
;

-- Native
UPDATE observation o JOIN taxon_country_sources a
ON o.species=a.taxon AND o.country=a.country
SET 
o.native_status_reason='Native to region, as per checklist',
o.native_status_sources=a.sources
WHERE o.native_status='N' AND a.native_status='native'
AND o.native_status_reason IS NULL
AND $CACHE_WHERE
;

-- Endemic
UPDATE observation o JOIN taxon_country_sources a
ON o.species=a.taxon AND o.country=a.country
SET 
o.native_status_reason='Endemic to region, as per checklist',
o.native_status_sources=a.sources
WHERE o.native_status='Ne' AND a.native_status='endemic'
AND o.native_status_reason IS NULL
AND $CACHE_WHERE
;

-- Present, status uncertain
UPDATE observation o JOIN taxon_country_sources a
ON o.species=a.taxon AND o.country=a.country
SET 
o.native_status_reason='Present in one or more checklists for region, status not indicated',
o.native_status_sources=a.sources
WHERE o.native_status='P' AND a.native_status='unknown'
AND o.native_status_reason IS NULL
AND $CACHE_WHERE
;

-- Absent from region
-- Flag by joining by checklist country
UPDATE observation o JOIN country_sources a
ON o.country=a.country
SET 
o.native_status_reason='Absent from all checklists for region',
o.native_status_sources=a.sources
WHERE o.native_status='A'
AND $CACHE_WHERE
;

-- Flag unknowns
UPDATE observation
SET native_status='UNK',
native_status_reason='Status unknown, no checklists for region of observation'
WHERE native_status='UNK' OR native_status IS NULL
AND $BATCH_WHERE_NA
AND $CACHE_WHERE_NA
;

-- 
-- Provide more detailed information for observations labeled
-- introduced due to higher taxa elsewhere
-- 

-- Endemic genera
UPDATE observation o JOIN endemic_taxon_sources a
ON o.genus=a.taxon
SET o.native_status_reason='Introduced, genus endemic to other region',
o.native_status_sources=a.sources
WHERE o.native_status='Ie' AND native_status_reason IS NULL
AND $CACHE_WHERE
;

-- Endemic families
UPDATE observation o JOIN endemic_taxon_sources a
ON o.family=a.taxon
SET o.native_status_reason='Introduced, family endemic to other region',
o.native_status_sources=a.sources
WHERE o.native_status='Ie' AND native_status_reason IS NULL
AND $CACHE_WHERE
;

";
sql_execute_multiple($sql);

// Some miscellaneous corrections
$sql="
-- Set null any empty strings added by the above steps
UPDATE observation
SET native_status_reason=NULL
WHERE native_status_reason IS NOT NULL AND trim(native_status_reason)=''
;
-- Fill in partial explanation for any records missed
UPDATE observation
SET native_status_reason=
CASE
WHEN native_status='Ne' THEN 'Endemic to region'
WHEN native_status='N' THEN 'Native to region'
WHEN native_status='I' THEN 'Introduced to region'
WHEN native_status='Ie' THEN 'Introduced, endemic to other region'
WHEN native_status='P' THEN 'Present in region, status uncertain'
ELSE native_status
END
WHERE native_status_reason IS NULL
;
";
sql_execute_multiple($sql);

// These rules should be changed as needed
// The first two updates are uncontroversial, but second
// two should be considered carefully.
// Currently, note that:
// 1. Absence counted as introduced
// 2. Presence counted as native rather than NULL
//echo "Updating isIntroduced...";
$sql="
UPDATE observation
SET isIntroduced=1
WHERE $BATCH_WHERE_NA
AND $CACHE_WHERE_NA 
AND native_status IN ('I','Ie')
;
UPDATE observation
SET isIntroduced=0
WHERE $BATCH_WHERE_NA
AND $CACHE_WHERE_NA
AND native_status IN ('N','Ne')
;
-- Assume native if present in checklist, without
-- further information
UPDATE observation
SET isIntroduced=0
WHERE $BATCH_WHERE_NA
AND $CACHE_WHERE_NA
AND native_status='P'
;
-- Assume introduced if absent from checklist
UPDATE observation
SET isIntroduced=1
WHERE $BATCH_WHERE_NA
AND $CACHE_WHERE_NA
AND native_status='A'
;
";
sql_execute_multiple($sql);

if ($echo_on) echo "done\r\n";
?>