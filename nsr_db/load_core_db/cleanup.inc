<?php

echo "  Dropping staging tables...";
$sql="
DROP TABLE IF EXISTS distribution_staging;
DROP TABLE IF EXISTS cultspp_staging;
DROP TABLE IF EXISTS poldiv_source_staging;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>