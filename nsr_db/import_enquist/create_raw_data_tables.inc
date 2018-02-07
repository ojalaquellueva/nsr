<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables:\r\n";

echo "  $tbl_raw_enquist_ow_endemics...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw_enquist_ow_endemics`;
CREATE TABLE `$tbl_raw_enquist_ow_endemics` (
region VARCHAR(100) DEFAULT NULL,
taxon VARCHAR(250) DEFAULT NULL,
INDEX (region),
INDEX (taxon)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

echo "  $tbl_raw_enquist_cultspp...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw_enquist_cultspp`;
CREATE TABLE `$tbl_raw_enquist_cultspp` (
taxon VARCHAR(250) DEFAULT NULL,
INDEX (taxon)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;


echo "  $tbl_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT,
taxon VARCHAR(250) DEFAULT NULL,
taxon_rank VARCHAR(50) DEFAULT NULL,
country VARCHAR(100) DEFAULT NULL,
stateProvince VARCHAR(150) DEFAULT NULL,
native_status VARCHAR(50) DEFAULT NULL,
native_status_details VARCHAR(100) DEFAULT NULL,
INDEX (id),
INDEX (taxon),
INDEX (taxon_rank),
INDEX (country),
INDEX (stateProvince),
INDEX (native_status),
INDEX (native_status_details)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

?>