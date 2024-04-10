<?php

/////////////////////////////////////////////////////////////////
// Separate taxon name from authors and dump to column `taxon`
//
// For hybrids, just dumps entire names without removing authors
// Made add some more sophisticated hybrid parsing later
/////////////////////////////////////////////////////////////////

echo "  Parsing taxon name...";
$sql="
UPDATE tropicos_raw
SET taxon=
CASE 
WHEN taxon_rank='species' THEN 
CONCAT_WS(' ',
strSplit(taxon_with_author,' ',1),
strSplit(taxon_with_author,' ',2)
)
WHEN taxon_rank='hybrid' THEN taxon_with_author
ELSE 
CONCAT_WS(' ',
strSplit(taxon_with_author,' ',1),
strSplit(taxon_with_author,' ',2),
strSplit(taxon_with_author,' ',3),
strSplit(taxon_with_author,' ',4)
)
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>