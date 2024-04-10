<?php

///////////////////////////////////////////////////////////////
// Add any permanent columns or indices needed
// Comment out whatever not needed
///////////////////////////////////////////////////////////////

echo "  Adding new columns and indexes...";

// Add a primary key
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
ADD UNIQUE INDEX(id)
;
";
sql_execute_multiple($dbh, $sql);

echo $done;

?>
