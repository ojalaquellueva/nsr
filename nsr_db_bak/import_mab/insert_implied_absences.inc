<?php

/////////////////////////////////////////////////////
// Flags a species as absent in all countries not
// in region of endemism. 
// This is only safe way to interpret assertions of
// a species being endemic to a multi-country region. 
// Can't definitively mark such species as endemic or
// even present in all countries comprising that region. 
// Would end up marking dozens of Cuban endemics as
// present on other West Indian islands where they 
// do not occur. But can at least mark these same 
// species as absent from all other
// countries.
// Note that we can do nothing with species listed
// as 'native' to multi-country regions.
/////////////////////////////////////////////////////

if ($cclist_countries=="") {
	$cclist_notin_where="1";
} else {
	$cclist_notin_where="b.country NOT IN ($cclist_countries)";
}

echo "Inserting implied absences due to endemism in checklist countries...";		
$sql="
INSERT INTO $tbl_raw (
source_name,
country,
taxon,
taxon_rank,
native_status,
inferred
)
SELECT DISTINCT
CONCAT('$src',' (implied absence due to endemism elsewhere)'),
b.country,
taxon,
taxon_rank,
'absent',
1
FROM $tbl_raw a, country b
LEFT JOIN (
SELECT DISTINCT country FROM $tbl_raw
) c
ON b.country=c.country
WHERE $cclist_notin_where
AND a.native_status='endemic'
AND c.country IS NULL
;
";
sql_execute_multiple($sql);	
echo $done;


?>