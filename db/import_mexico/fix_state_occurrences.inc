<?php

///////////////////////////////////////////////////////////////
// Reset any state-level endemics to 'native'
///////////////////////////////////////////////////////////////

echo "Setting state-level occurrences from 'endemic' to 'native'...";

// Add a primary key
$sql="
UPDATE distribution_staging
SET native_status='native'
WHERE state_province IS NOT NULL 
AND native_status='endemic'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>