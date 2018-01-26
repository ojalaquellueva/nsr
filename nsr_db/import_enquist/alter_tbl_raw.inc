<?php

///////////////////////////////////////////////////////////////
// Add any permanent columns or indices needed
// Comment out whatever not needed
///////////////////////////////////////////////////////////////

echo "Altering raw data tables\r\n";

echo "  Adding new columns and indexes:\r\n";
echo "    `is_country`...";
$sql="
ALTER TABLE $tbl_raw_enquist_ow_endemics
ADD COLUMN country VARCHAR(100) DEFAULT NULL,
ADD INDEX (country)
;
";
sql_execute_multiple($sql);

echo $done;

?>
