<?php

///////////////////////////////////////////////////////
// Standardize variant political division spellings
///////////////////////////////////////////////////////

echo "  Standardizing country names...";
$sql="
UPDATE distribution d join countryName c
ON d.country=c.countryName
SET d.country=c.countryNameStd
WHERE d.country<>c.countryNameStd
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>