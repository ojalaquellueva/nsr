<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data table $tbl_raw:\r\n";

echo "  $tbl_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
`AcceptedSymbol`VARCHAR(50) DEFAULT NULL,
`SynonymSymbol`VARCHAR(50) DEFAULT NULL,
`ScientificName`VARCHAR(250) DEFAULT NULL,
`StateAndProvince`VARCHAR(500) DEFAULT NULL,
`Genus`VARCHAR(50) DEFAULT NULL,
`Family`VARCHAR(50) DEFAULT NULL,
`NativeStatus`VARCHAR(500) DEFAULT NULL
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo "done";
	
?>

