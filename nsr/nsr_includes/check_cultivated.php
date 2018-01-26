<?php

////////////////////////////////$CACHE_WHERE////////////////////////////////
// Updates is_cultivated_taxon
//
// Sets is_cultivated_taxon=1 if the taxon is listed as 
// generally cultivated. Does not necessarily mean that the 
// individual plant is cultivated, although likely. It's up
// to the user to decide how to handle observation of taxa
// which are exclusively or widely cultivated
////////////////////////////////////////////////////////////////

//echo "Updating cultivated status...";

if ($echo_on) echo "  Checking cultivated...";

$sql="
-- species
UPDATE observation o JOIN cultspp c
ON o.species=c.taxon
SET o.is_cultivated_taxon=1
WHERE $BATCH_WHERE
;
";
sql_execute_multiple($sql);	

if ($echo_on) echo "done\r\n";


?>