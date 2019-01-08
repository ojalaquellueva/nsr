<?php

///////////////////////////////////////////////////////////////
// Add any permanent columns or indices needed
// Comment out whatever not needed
///////////////////////////////////////////////////////////////

echo "  Adding new columns and indexes...";

// Add a primary key
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY FIRST,
ADD UNIQUE INDEX(id)
;
";
sql_execute_multiple($dbh, $sql);

// Add source_name
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN source_name VARCHAR(100) DEFAULT '$src' AFTER id
;
";
sql_execute_multiple($dbh, $sql);

// Add native_status
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN native_status VARCHAR(100) DEFAULT 'endemic' AFTER taxon_rank
;
";
sql_execute_multiple($dbh, $sql);

// Adding column inferred (0,1)
// 0=explicit, in original raw data
// 1=inferred, added due to endemic in raw data
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN inferred INT(1) DEFAULT 0 AFTER native_status
;
";
sql_execute_multiple($dbh, $sql);

// Add include field
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN include INT(1) DEFAULT 1
;
";
sql_execute_multiple($dbh, $sql);

// Add remaining indexes
$sql="
ALTER TABLE `$tbl_raw`
ADD INDEX (source_name),
ADD INDEX (country),
ADD INDEX (inferred),
ADD INDEX (taxon),
ADD INDEX (taxon_rank),
ADD INDEX (native_status),
ADD INDEX (include)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>
