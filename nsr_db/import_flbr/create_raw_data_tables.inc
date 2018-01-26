<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables:\r\n";

echo "  $tbl_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY,
taxon_id BIGINT NOT NULL,
taxon_rank VARCHAR(50) DEFAULT NULL,
taxon_with_author VARCHAR(250) DEFAULT NULL, 
family VARCHAR(250) DEFAULT NULL, 
genus VARCHAR(250) DEFAULT NULL, 
species VARCHAR(250) DEFAULT NULL, 
taxon VARCHAR(250) DEFAULT NULL, 
state_code VARCHAR(50) DEFAULT NULL, 
country VARCHAR(100) DEFAULT NULL, 
state_province VARCHAR(100) DEFAULT NULL, 
native_status VARCHAR(50) DEFAULT NULL, 
cult_status VARCHAR(50) DEFAULT NULL, 
include INT(1) DEFAULT 1
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;


echo "  $tbl_dist_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_dist_raw`;
CREATE TABLE $tbl_dist_raw (
id BIGINT NOT NULL,
locality VARCHAR(250) DEFAULT NULL,
countryCode VARCHAR(250) DEFAULT NULL,
establishmentMeans VARCHAR(250) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

echo "  $tbl_taxon_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_taxon_raw`;
CREATE TABLE $tbl_taxon_raw (
id BIGINT NOT NULL,
taxonID BIGINT DEFAULT NULL,
acceptedNameUsageID BIGINT DEFAULT NULL,
parentNameUsageID BIGINT DEFAULT NULL,
originalNameUsageID BIGINT DEFAULT NULL,
scientificName VARCHAR(250) DEFAULT NULL,
acceptedNameUsage VARCHAR(250) DEFAULT NULL,
parentNameUsage VARCHAR(250) DEFAULT NULL,
namePublishedIn VARCHAR(250) DEFAULT NULL,
namePublishedInYear VARCHAR(250) DEFAULT NULL,
higherClassification VARCHAR(250) DEFAULT NULL,
phylum VARCHAR(250) DEFAULT NULL,
`class` VARCHAR(250) DEFAULT NULL,
`order` VARCHAR(250) DEFAULT NULL,
family VARCHAR(250) DEFAULT NULL,
genus VARCHAR(250) DEFAULT NULL,
specificEpithet VARCHAR(250) DEFAULT NULL,
infraspecificEpithet VARCHAR(250) DEFAULT NULL,
taxonRank VARCHAR(250) DEFAULT NULL,
scientificNameAuthorship VARCHAR(250) DEFAULT NULL,
taxonomicStatus VARCHAR(250) DEFAULT NULL,
nomenclaturalStatus VARCHAR(250) DEFAULT NULL,
modified VARCHAR(250) DEFAULT NULL,
bibliographicCitation VARCHAR(500) DEFAULT NULL,
`references` VARCHAR(500) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

?>