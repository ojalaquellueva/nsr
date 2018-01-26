<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables:\r\n";

echo "  $tbl_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
species_id VARCHAR(255) DEFAULT NULL,
family VARCHAR(255) DEFAULT NULL,
species_with_author VARCHAR(255) DEFAULT NULL,
native_status VARCHAR(255) DEFAULT NULL,
state1 VARCHAR(255) DEFAULT NULL,
state2 VARCHAR(255) DEFAULT NULL,
state3 VARCHAR(255) DEFAULT NULL,
state4 VARCHAR(255) DEFAULT NULL,
state5 VARCHAR(255) DEFAULT NULL,
state6 VARCHAR(255) DEFAULT NULL,
state7 VARCHAR(255) DEFAULT NULL,
state8 VARCHAR(255) DEFAULT NULL,
state9 VARCHAR(255) DEFAULT NULL,
state10 VARCHAR(255) DEFAULT NULL,
state11 VARCHAR(255) DEFAULT NULL,
state12 VARCHAR(255) DEFAULT NULL,
state13 VARCHAR(255) DEFAULT NULL,
state14 VARCHAR(255) DEFAULT NULL,
state15 VARCHAR(255) DEFAULT NULL,
state16 VARCHAR(255) DEFAULT NULL,
state17 VARCHAR(255) DEFAULT NULL,
state18 VARCHAR(255) DEFAULT NULL,
state19 VARCHAR(255) DEFAULT NULL,
state20 VARCHAR(255) DEFAULT NULL,
state21 VARCHAR(255) DEFAULT NULL,
state22 VARCHAR(255) DEFAULT NULL,
state23 VARCHAR(255) DEFAULT NULL,
state24 VARCHAR(255) DEFAULT NULL,
state25 VARCHAR(255) DEFAULT NULL,
state26 VARCHAR(255) DEFAULT NULL,
state27 VARCHAR(255) DEFAULT NULL,
state28 VARCHAR(255) DEFAULT NULL,
state29 VARCHAR(255) DEFAULT NULL,
state30 VARCHAR(255) DEFAULT NULL,
state31 VARCHAR(255) DEFAULT NULL,
state32 VARCHAR(255) DEFAULT NULL
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

echo "  $tbl_species_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_species_raw`;
CREATE TABLE $tbl_species_raw (
species_id VARCHAR(255) DEFAULT NULL,
family VARCHAR(255) DEFAULT NULL,
bad VARCHAR(255) DEFAULT NULL,
species VARCHAR(255) DEFAULT NULL
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

echo "Indexing tables...";
$sql="
ALTER TABLE $tbl_species_raw
ADD INDEX (species_id); 
ALTER TABLE $tbl_raw
ADD INDEX (species_id); 
";
sql_execute_multiple($sql);
echo $done;

	
?>

