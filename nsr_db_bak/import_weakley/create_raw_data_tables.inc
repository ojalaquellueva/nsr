<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables:\r\n";

echo "  `$tbl_weakley_exotic_part_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_weakley_exotic_part_raw`;
CREATE TABLE `$tbl_weakley_exotic_part_raw` (
taxon VARCHAR(250) DEFAULT NULL,
stateProvinceCode VARCHAR(4) DEFAULT NULL,
INDEX (taxon),
INDEX (stateProvinceCode)
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

echo "  `$tbl_weakley_exotic_all_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_weakley_exotic_all_raw`;
CREATE TABLE `$tbl_weakley_exotic_all_raw` (
taxon VARCHAR(250) DEFAULT NULL,
INDEX (taxon)
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

echo "  `$tbl_weakley_origin_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_weakley_origin_raw`;
CREATE TABLE `$tbl_weakley_origin_raw` (
family VARCHAR(150) DEFAULT NULL,
taxon VARCHAR(250) DEFAULT NULL,
origin VARCHAR(50) DEFAULT NULL,
INDEX (family),
INDEX (taxon),
INDEX (origin)
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;
	
echo "  `$tbl_weakley_poldivs_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_weakley_poldivs_raw`;
CREATE TABLE `$tbl_weakley_poldivs_raw` (
stateProvinceCode VARCHAR(4) DEFAULT NULL,
country VARCHAR(50) DEFAULT NULL,
INDEX (stateProvinceCode),
INDEX (country)
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

echo "  `$tbl_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE `$tbl_raw` (
id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT,
taxon VARCHAR(250) DEFAULT NULL,
taxon_rank VARCHAR(50) DEFAULT NULL,
country VARCHAR(50) DEFAULT NULL,
stateProvince VARCHAR(150) DEFAULT NULL,
native_status VARCHAR(50) DEFAULT NULL,
INDEX (id),
INDEX (taxon),
INDEX (taxon_rank),
INDEX (country),
INDEX (stateProvince),
INDEX (native_status)
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

?>