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
sql_execute_multiple($sql);

// Add taxon field
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN taxon VARCHAR(250) DEFAULT NULL,
ADD INDEX (taxon)
;
";
sql_execute_multiple($sql);

// Add taxon rank field
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN taxon_rank VARCHAR(25) DEFAULT NULL,
ADD INDEX (taxon_rank)
;
";
sql_execute_multiple($sql);

// Add include field
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN include INT(1) DEFAULT 1,
ADD INDEX (include)
;
";
sql_execute_multiple($sql);
echo $done;

?>
