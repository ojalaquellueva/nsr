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

// Add taxon, rank and include columns
$sql="
-- taxon columns
ALTER TABLE `$tbl_raw`
ADD COLUMN family VARCHAR(250) DEFAULT NULL AFTER taxon_id,
ADD INDEX (family)
;
ALTER TABLE `$tbl_raw`
ADD COLUMN genus VARCHAR(250) DEFAULT NULL AFTER taxon,
ADD INDEX (genus)
;
ALTER TABLE `$tbl_raw`
ADD COLUMN species VARCHAR(250) DEFAULT NULL AFTER genus,
ADD INDEX (species)
;


-- taxon rank
ALTER TABLE `$tbl_raw`
ADD COLUMN taxon_rank VARCHAR(25) DEFAULT NULL AFTER taxon_id,
ADD INDEX (taxon_rank)
;

-- Include field
ALTER TABLE `$tbl_raw`
ADD COLUMN include INT(1) DEFAULT 1,
ADD INDEX (include)
;
";
sql_execute_multiple($sql);
echo $done;

?>
