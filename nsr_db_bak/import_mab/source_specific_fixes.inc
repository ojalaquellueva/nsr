<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Removing garbage rows...";
$sql="
DELETE FROM `$tbl_raw`
WHERE taxon IS NULL
;
DELETE FROM `$tbl_raw`
WHERE country='Unknown Origin'
;
";
sql_execute_multiple($sql);
echo $done;

// This next operation can't use function sql_execute_multiple
// because of embedded semi-colon
echo "  Removing html in taxon field...";
$sql="
UPDATE `$tbl_raw`
SET taxon='Hondurodendron'
WHERE taxon LIKE 'Hondurodendron%' 
AND taxon_rank='Genus'
;
";
sql_execute_multiple($sql);
echo $done;

// Converting non-standard country names
echo "  Converting non-standard country names...";
$sql="
UPDATE `$tbl_raw`
SET country=
CASE
WHEN country LIKE '%Ivoire' THEN 'Ivory Coast'
WHEN country = 'Republic of South Africa' THEN 'South Africa'
WHEN country = 'Timor' THEN 'East Timor'
WHEN country = 'United States of America' THEN 'United States'
ELSE country
END
;
";
sql_execute_multiple($sql);
echo $done;

echo "  Splitting 'Korean Peninsula into separate records for N & S Korea...";
$sql="
INSERT INTO mab_raw (
country,
taxon,
taxon_rank,
added_by,
include
)
VALUES
(
'North Korea',
'Hanabusaya',
'Genus',
'B. Boyle',
1
),
(
'North Korea',
'Abeliophyllum',
'Genus',
'B. Boyle',
1
)
;
UPDATE `$tbl_raw`
SET country='South Korea'
WHERE country='Korean Peninsula'
;
";
sql_execute_multiple($sql);
echo $done;

?>