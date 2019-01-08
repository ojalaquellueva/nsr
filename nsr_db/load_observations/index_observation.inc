<?php

echo "Indexing table observation...";
$sql="
ALTER TABLE observation
ADD INDEX (family),
ADD INDEX (genus),
ADD INDEX (species),
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish)
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>