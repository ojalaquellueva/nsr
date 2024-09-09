<?php

///////////////////////////////////////////////////////////////
// Rename staging table with source-specific suffix
///////////////////////////////////////////////////////////////

$tbl_staging_curr_src = "distribution_staging_" . $source_name;

echo "Renaming staging table to `$tbl_staging_curr_src`...";
$sql="
DROP TABLE IF EXISTS $tbl_staging_curr_src
;
ALTER TABLE `distribution_staging` RENAME TO `$tbl_staging_curr_src`
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>