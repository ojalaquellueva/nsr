<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables:\r\n";

echo "  ipane_raw...";
$sql="
DROP TABLE IF EXISTS `ipane_raw`;
CREATE TABLE ipane_raw (
ScientificName VARCHAR(150) DEFAULT NULL,
State VARCHAR(5) DEFAULT NULL,
Locality VARCHAR(150) DEFAULT NULL,
Latitude VARCHAR(150) DEFAULT NULL,
Longitude VARCHAR(150) DEFAULT NULL,
Elevation VARCHAR(150) DEFAULT NULL,
Date VARCHAR(150) DEFAULT NULL,
HabitatType VARCHAR(150) DEFAULT NULL,
Abundance VARCHAR(150) DEFAULT NULL,
Distribution VARCHAR(150) DEFAULT NULL,
PercentageCover VARCHAR(150) DEFAULT NULL,
EvidenceOfReproduction VARCHAR(150) DEFAULT NULL,
INDEX (ScientificName)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo "done";
	
?>

