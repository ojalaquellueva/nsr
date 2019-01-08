<?php

/////////////////////////////////////////////////////////////////
// Separate taxon name from authors and dump to column `taxon`
//
// For hybrids, just dumps entire names without removing authors
// Made add some more sophisticated hybrid parsing later
/////////////////////////////////////////////////////////////////

echo "  Parsing taxon name...";
$sql="
UPDATE `$tbl_raw`
SET taxon=
CASE 
WHEN taxon_rank='species' THEN 
CONCAT_WS(' ',
strSplit(`$fld_scientific_name`,' ',1),
strSplit(`$fld_scientific_name`,' ',2)
)
WHEN taxon_rank='hybrid' THEN `$fld_scientific_name`
ELSE 
CONCAT_WS(' ',
strSplit(`$fld_scientific_name`,' ',1),
strSplit(`$fld_scientific_name`,' ',2),
strSplit(`$fld_scientific_name`,' ',3),
strSplit(`$fld_scientific_name`,' ',4)
)
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>