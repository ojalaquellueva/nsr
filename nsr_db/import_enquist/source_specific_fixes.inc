<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Source-specific corrections:\r\n";

echo "    fixing misc glitches...";
$sql="
-- Remove underscores
UPDATE $tbl_raw_enquist_ow_endemics
SET taxon=REPLACE(taxon,'_',' ')
WHERE taxon LIKE '%_%'
;
UPDATE $tbl_raw_enquist_ow_endemics
SET region=REPLACE(region,'_',' ')
WHERE region LIKE '%_%'
;
-- Misspellings
UPDATE $tbl_raw_enquist_ow_endemics
SET region='Australia'
WHERE region='Austrailia'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Standardizing countries...";
$sql="
UPDATE $tbl_raw_enquist_ow_endemics a JOIN countryName b
ON a.region=b.countryName
SET a.country=b.countryNameStd
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>