<?php

///////////////////////////////////////////////////////////////
// Add any permanent columns or indices needed
// Comment out whatever not needed
///////////////////////////////////////////////////////////////

echo "  Adding new columns and indexes...";

// Add stateProvince name field to political division table
$sql="
ALTER TABLE `$tbl_weakley_poldivs_raw`
ADD COLUMN stateProvince VARCHAR(50) DEFAULT NULL,
ADD INDEX (stateProvince);
";
sql_execute_multiple($sql);

// Add isOldWorld name field to origin table
$sql="
ALTER TABLE `$tbl_weakley_origin_raw`
ADD COLUMN isOldWorld INT(1) DEFAULT 0,
ADD INDEX (isOldWorld);
";
sql_execute_multiple($sql);

echo $done;

?>
