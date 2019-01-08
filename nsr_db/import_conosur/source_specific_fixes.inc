<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Removing extra spaces from taxon name...";
$sql="
-- Three spaces
UPDATE `$tbl_raw` 
SET taxon=REPLACE(taxon,'   ',' ')
WHERE taxon LIKE '%   %'
;
-- Two spaces
UPDATE `$tbl_raw` 
SET taxon=REPLACE(taxon,'  ',' ')
WHERE taxon LIKE '%  %'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Fixing miscellaneous taxon name errors...";
$sql="
UPDATE `$tbl_raw` 
SET taxon='Muhlenbergia angustata x rigida'
WHERE taxon='Muhlenbergia angustata (J. Presl) Kunth x M. rigida'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Populating species...";
$sql="
-- non-hybrids
UPDATE `$tbl_raw` 
SET species=CONCAT_WS(' ',
strSplit(taxon,' ',1),
strSplit(taxon,' ',2)
)
WHERE taxon LIKE '% %'
AND taxon NOT LIKE '% x %'
;

-- hybrids
UPDATE `$tbl_raw` 
SET species=taxon
WHERE taxon LIKE '% %'
AND taxon LIKE '% x %'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Populating genus...";
$sql="
UPDATE `$tbl_raw` 
SET genus=strSplit(taxon,' ',1)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

// This is a hack. Allow country records to be appended, but
// not province records. Ultimately need to parse dist_string,
// extract province codes and translate to actual names.
echo "  Populating missing distribution codes for Chile...";
$sql="
UPDATE `$tbl_raw` 
SET Chile='Chile'
WHERE dist_string LIKE '%CHL(%'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;





?>