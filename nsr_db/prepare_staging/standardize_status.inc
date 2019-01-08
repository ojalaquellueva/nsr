<?php

//////////////////////////////////////////////////
// Standardize status codes
// This is a hack because status
// codes should are standardized
// earlier during import, but inconsistently.
// This second standardization is a hack until
// I get around to cleaning up the import code
//////////////////////////////////////////////////

echo "  Re-standardizing native status codes...";
$sql="
UPDATE distribution_staging
SET native_status='introduced'
WHERE native_status='not native' OR native_status='non-native' OR native_status='Introduced' OR native_status='absent'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>