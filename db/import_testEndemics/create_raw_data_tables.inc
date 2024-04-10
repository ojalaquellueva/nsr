<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables:\r\n";

echo "  ipane_raw...";
$sql="
DROP TABLE IF EXISTS `testEndemics_raw`;
CREATE TABLE testEndemics_raw (
country VARCHAR(150) DEFAULT NULL,
taxon VARCHAR(250) DEFAULT NULL,
taxon_rank VARCHAR(50) DEFAULT NULL,
INDEX (taxon)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo "done";
	
?>

