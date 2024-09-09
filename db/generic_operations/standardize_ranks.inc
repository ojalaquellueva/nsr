<?php

///////////////////////////////////////////////////////////
// Assume the rank column has already been somewhat standardized
// on input to this limited set of options
////////////////////////////////////////////////////////////

echo "Standardizing ranks..";
$sql="
UPDATE distribution 
SET taxon_rank=
CASE
WHEN TRIM(taxon_rank)='Class ' THEN 'class'
WHEN TRIM(taxon_rank)='cv.' THEN 'cultivar'
WHEN TRIM(taxon_rank)='family' THEN 'family'
WHEN TRIM(taxon_rank)='fo.' THEN 'forma'
WHEN TRIM(taxon_rank)='genus' THEN 'genus'
WHEN TRIM(taxon_rank)='hybrid' THEN 'hybrid'
WHEN TRIM(taxon_rank)='Order' THEN 'order'
WHEN TRIM(taxon_rank)='species' THEN 'species'
WHEN TRIM(taxon_rank)='subsp' THEN 'subspecies'
WHEN TRIM(taxon_rank)='subspecies' THEN 'subspecies'
WHEN TRIM(taxon_rank)='var.' THEN 'variety'
WHEN TRIM(taxon_rank)='variety' THEN 'variety'
ELSE TRIM(taxon_rank)
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;


?>