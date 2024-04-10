<?php

//////////////////////////////////////////////////////
// Temporary hack until I figure out what is going on
// with script parse_usda_plants. Basically, it is setting
// all state occurrences to unknown instead of native.
// Sets all status='unknow' to 'native'
//////////////////////////////////////////////////////

echo "  Standardizing status codes...";
$sql="
UPDATE `$tbl_raw`
SET native_status='native'
WHERE native_status IN ('Unknown','unknown','UNK','unk')
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>