<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables:\r\n";

echo "  $tbl_vascan_taxon_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_vascan_taxon_raw`;
CREATE TABLE $tbl_vascan_taxon_raw (
id INT(11) UNSIGNED NOT NULL,
taxonID INT(11) UNSIGNED NOT NULL,
acceptedNameUsageID INT(11) UNSIGNED NOT NULL,
parentNameUsageID INT(11) UNSIGNED NOT NULL,
nameAccordingToID VARCHAR(250) DEFAULT NULL,
scientificName VARCHAR(250) DEFAULT NULL,
acceptedNameUsage VARCHAR(250) DEFAULT NULL,
parentNameUsage VARCHAR(250) DEFAULT NULL,
nameAccordingTo VARCHAR(250) DEFAULT NULL,
higherClassification VARCHAR(250) DEFAULT NULL,
class VARCHAR(250) DEFAULT NULL,
`order` VARCHAR(250) DEFAULT NULL,
family VARCHAR(250) DEFAULT NULL,
genus VARCHAR(250) DEFAULT NULL,
subgenus VARCHAR(250) DEFAULT NULL,
specificEpithet VARCHAR(250) DEFAULT NULL,
infraspecificEpithet VARCHAR(250) DEFAULT NULL,
taxonRank VARCHAR(250) DEFAULT NULL,
scientificNameAuthorship VARCHAR(250) DEFAULT NULL,
taxonomicStatus VARCHAR(250) DEFAULT NULL,
modified VARCHAR(250) DEFAULT NULL,
license VARCHAR(250) DEFAULT NULL,
bibliographicCitation VARCHAR(250) DEFAULT NULL,
`references` VARCHAR(250) DEFAULT NULL,
PRIMARY KEY (id),
INDEX (acceptedNameUsageID),
INDEX (parentNameUsageID),
INDEX(scientificName),
INDEX(family),
INDEX(genus),
INDEX(taxonRank),
INDEX(taxonomicStatus)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  $tbl_vascan_distribution_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_vascan_distribution_raw`;
CREATE TABLE $tbl_vascan_distribution_raw (
id INT(11) UNSIGNED NOT NULL,
locationID VARCHAR(250) DEFAULT NULL,
locality VARCHAR(250) DEFAULT NULL,
countryCode VARCHAR(250) DEFAULT NULL,
occurrenceStatus VARCHAR(250) DEFAULT NULL,
establishmentMeans VARCHAR(250) DEFAULT NULL,
source VARCHAR(250) DEFAULT NULL,
occurrenceRemarks VARCHAR(250) DEFAULT NULL,
INDEX(id),
INDEX(occurrenceStatus),
INDEX(establishmentMeans)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  $tbl_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
id INT(11) UNSIGNED NOT NULL,
taxon VARCHAR(250) DEFAULT NULL,
taxon_rank VARCHAR(50) DEFAULT NULL,
country VARCHAR(100) DEFAULT NULL,
stateProvince VARCHAR(150) DEFAULT NULL,
native_status VARCHAR(50) DEFAULT NULL,
INDEX (id),
INDEX (taxon),
INDEX (taxon_rank),
INDEX (country),
INDEX (stateProvince),
INDEX (native_status)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>

