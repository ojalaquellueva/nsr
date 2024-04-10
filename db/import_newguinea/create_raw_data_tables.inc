<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables\r\n";

$tbl_raw=$src."_raw";
echo "  `$tbl_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
`higher_taxon` VARCHAR(250) DEFAULT NULL,
family_original VARCHAR(250) DEFAULT NULL,
fullname_original VARCHAR(250) DEFAULT NULL,
taxonomic_status_TNRS VARCHAR(250) DEFAULT NULL,
family_TNRS VARCHAR(250) DEFAULT NULL,
acceptedname_TNRS VARCHAR(250) DEFAULT NULL,
authorname_TNRS VARCHAR(250) DEFAULT NULL,
family_expert_verified VARCHAR(250) DEFAULT NULL,
fullname_expert_verified VARCHAR(250) DEFAULT NULL,
authorname_expert_verified VARCHAR(250) DEFAULT NULL,
native VARCHAR(250) DEFAULT NULL,
endemic VARCHAR(250) DEFAULT NULL,
IDN VARCHAR(250) DEFAULT NULL,
PNG VARCHAR(250) DEFAULT NULL,
life_form VARCHAR(250) DEFAULT NULL,
checked_by VARCHAR(250) DEFAULT NULL,
reference_consulted VARCHAR(250) DEFAULT NULL,
notes VARCHAR(250) DEFAULT NULL,
notes2 VARCHAR(250) DEFAULT NULL,
woody VARCHAR(250) DEFAULT NULL,
basionym_year VARCHAR(250) DEFAULT NULL
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

$tbl_raw_final=$src."_raw_final";
echo "  `$tbl_raw_final`...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw_final`;
CREATE TABLE $tbl_raw_final (
taxon VARCHAR(250) DEFAULT NULL,
taxon_rank VARCHAR(250) DEFAULT NULL,
country VARCHAR(250) DEFAULT NULL,
state_province VARCHAR(250) DEFAULT NULL,
county_parish VARCHAR(250) DEFAULT NULL,
native_status VARCHAR(250) DEFAULT NULL
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>