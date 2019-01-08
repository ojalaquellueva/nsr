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

// Add taxon columns
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN taxon VARCHAR(250) DEFAULT NULL AFTER family,
ADD INDEX (taxon)
;
ALTER TABLE `$tbl_raw`
ADD COLUMN genus VARCHAR(250) DEFAULT NULL AFTER taxon,
ADD INDEX (genus)
;
ALTER TABLE `$tbl_raw`
ADD COLUMN species VARCHAR(250) DEFAULT NULL AFTER genus,
ADD INDEX (species)
;
";
sql_execute_multiple($dbh, $sql);

// Add taxon rank field
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN taxon_rank VARCHAR(25) DEFAULT NULL AFTER taxon,
ADD INDEX (taxon_rank)
;
";
sql_execute_multiple($dbh, $sql);

// Add include field
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN include INT(1) DEFAULT 1,
ADD INDEX (include)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>
