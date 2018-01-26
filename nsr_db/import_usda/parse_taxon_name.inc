<?php

/////////////////////////////////////////////////////////////////
// Reforms scientific name of infraspecific taxa using
// standardized rank indicator. For genera, species and hybrids, 
// just dump entire name. USDA dump does not include authors 
// so no need to remove.
/////////////////////////////////////////////////////////////////

echo "  Parsing taxon name...";
$sql="
UPDATE `$tbl_raw`
SET taxon=`$fld_scientific_name`
WHERE taxon_rank='species' OR taxon_rank='genus' 
OR taxon_rank='family' OR taxon_rank='hybrid'
;  
UPDATE `$tbl_raw`
SET taxon=
CONCAT_WS(' ',
strSplit(`$fld_scientific_name`,' ',1),
strSplit(`$fld_scientific_name`,' ',2),
strSplit(`$fld_scientific_name`,' ',3),
strSplit(`$fld_scientific_name`,' ',4)
)
WHERE taxon IS NULL
;
";
sql_execute_multiple($sql);
echo $done;

?>