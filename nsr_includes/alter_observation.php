<?php


echo "Standardizing Newfoundland and Labrador as single political division...";
$sql="
-- Merge Newfoundland and Labrador
UPDATE observation
SET state_province='Newfoundland and Labrador'
WHERE country='Canada' 
AND state_province LIKE '%Newfoundland%' OR state_province LIKE '%Labrador%'
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>



