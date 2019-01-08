<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Source-specific corrections...";

// Fix non-standard stateProvince codes
$sql="
UPDATE $tbl_weakley_poldivs_raw
SET stateProvinceCode=
CASE
WHEN stateProvinceCode='PN' THEN 'PA'
WHEN stateProvinceCode='NL' THEN 'NF'
ELSE stateProvinceCode
END;
UPDATE $tbl_weakley_exotic_part_raw
SET stateProvinceCode=
CASE
WHEN stateProvinceCode='PN' THEN 'PA'
WHEN stateProvinceCode='NL' THEN 'NF'
ELSE stateProvinceCode
END;
";
sql_execute_multiple($dbh, $sql);

// Replace underscores with plain hybrid 'x'
$sql="
UPDATE $tbl_weakley_exotic_part_raw
SET taxon=REPLACE(taxon,'_','x ')
WHERE taxon LIKE '%\_%';
UPDATE $tbl_weakley_exotic_all_raw
SET taxon=REPLACE(taxon,'_','x ')
WHERE taxon LIKE '%\_%';
UPDATE $tbl_weakley_origin_raw
SET taxon=REPLACE(taxon,'_','x ')
WHERE taxon LIKE '%\_%';
";
sql_execute_multiple($dbh, $sql);

// Replace ssp. with subsp.
$sql="
UPDATE $tbl_weakley_exotic_part_raw
SET taxon=REPLACE(taxon,'ssp.','subsp.')
WHERE taxon LIKE '%ssp.%';
UPDATE $tbl_weakley_exotic_all_raw
SET taxon=REPLACE(taxon,'ssp.','subsp.')
WHERE taxon LIKE '%ssp.%';
UPDATE $tbl_weakley_origin_raw
SET taxon=REPLACE(taxon,'ssp.','subsp.')
WHERE taxon LIKE '%ssp.%';
";
sql_execute_multiple($dbh, $sql);

echo $done;

?>