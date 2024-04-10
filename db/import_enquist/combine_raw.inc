<?php

/////////////////////////////////////////////////////////
// Load country occurrences and inferred New World endemics
// into main raw table
/////////////////////////////////////////////////////////

echo "Combining country occurrences and inferred New World endemics:\r\n";

echo "  Inserting species endemic to specific Old World countries...";
$sql="
INSERT INTO $tbl_raw (
taxon,
country,
native_status
)
SELECT DISTINCT
TRIM(taxon),
country,
'endemic'
FROM $tbl_raw_enquist_ow_endemics
WHERE country IS NOT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Inserting Old World endemics as exotics in each New World country...";
// Note cartesian product 
// Inserts a record for each Old World taxon in every New World country,
// with status='Introduced'
$sql="
INSERT INTO $tbl_raw (
taxon,
country,
native_status,
native_status_details
)
SELECT DISTINCT
a.taxon,
b.country,
'introduced',
'Introduced status inferred from endemism in Old World'
FROM 
(
SELECT DISTINCT taxon
FROM $tbl_raw_enquist_ow_endemics
) AS a, 
(
SELECT DISTINCT countryNameStd AS country
FROM countryName 
WHERE isNewWorld=1
) AS b
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

// Fix blank taxon rows
// Not sure how these creep in
$sql="
DELETE FROM $tbl_raw
WHERE taxon IS NULL
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>