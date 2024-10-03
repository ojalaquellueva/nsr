<?php

/////////////////////////////////////////////////////
// Add extra columns for standardizes political 
// division names, etc 
/////////////////////////////////////////////////////

echo "Altering tables:\n";

echo "  Altering table `$tbl_raw`...";
$sql="
ALTER TABLE $tbl_raw 
ADD COLUMN id INT PRIMARY KEY AUTO_INCREMENT FIRST,
ADD COLUMN accepted_rank VARCHAR(50) DEFAULT NULL,
ADD COLUMN establishment VARCHAR(50) DEFAULT NULL,
ADD COLUMN poldiv_full_verbatim VARCHAR(750) DEFAULT NULL,
ADD COLUMN country_verbatim VARCHAR(250) DEFAULT NULL,
ADD COLUMN state_province_verbatim VARCHAR(250) DEFAULT NULL,
ADD COLUMN county_parish_verbatim VARCHAR(250) DEFAULT NULL,
ADD COLUMN poldiv_full VARCHAR(750) DEFAULT NULL,
ADD COLUMN country_id INT(11) DEFAULT NULL,
ADD COLUMN state_province_id INT(11) DEFAULT NULL,
ADD COLUMN county_parish_id INT(11) DEFAULT NULL,
ADD COLUMN country VARCHAR(250) DEFAULT NULL,
ADD COLUMN state_province VARCHAR(250) DEFAULT NULL,
ADD COLUMN county_parish VARCHAR(250) DEFAULT NULL,
ADD COLUMN poldiv_matched VARCHAR(250) DEFAULT NULL,
ADD COLUMN match_status VARCHAR(250) DEFAULT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Indexing `$tbl_raw`...";
$sql="
ALTER TABLE $tbl_raw 
ADD INDEX (name),
ADD INDEX (`rank`),
ADD INDEX (introduced),
ADD INDEX (taxonomicStatus),
ADD INDEX (area_name),
ADD INDEX (match_status),
ADD INDEX (tdwgCodeL3),
ADD INDEX (poldiv_full_verbatim)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Indexing table `$tbl_region_codes`...";
$sql="
ALTER TABLE $tbl_region_codes 
ADD COLUMN poldiv_full VARCHAR(500),
ADD INDEX (code),
ADD INDEX (code_type),
ADD INDEX (region),
ADD INDEX (poldiv_full),
ADD INDEX (country),
ADD INDEX (state_province)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>