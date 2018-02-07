<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Source-specific corrections...";

// Delete any records of taxa higher than species
// Delete any records without at least a country
$sql="
DELETE FROM $tbl_raw 
WHERE taxon NOT LIKE '% %' OR taxon IS NULL OR TRIM(taxon)='';
DELETE FROM $tbl_raw 
WHERE country IS NULL OR TRIM(country)='';
";
sql_execute_multiple($sql);
echo $done;

?>