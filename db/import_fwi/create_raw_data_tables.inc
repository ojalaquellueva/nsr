<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables:\r\n";

echo "  $tbl_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
family VARCHAR(255) DEFAULT NULL,
genus VARCHAR(255) DEFAULT NULL,
epithet VARCHAR(255) DEFAULT NULL,
author VARCHAR(255) DEFAULT NULL,
publication VARCHAR(255) DEFAULT NULL,
westIndies VARCHAR(255) DEFAULT NULL,
greaterAntilles VARCHAR(255) DEFAULT NULL,
jamaica VARCHAR(255) DEFAULT NULL,
cuba VARCHAR(255) DEFAULT NULL,
caymanIsland VARCHAR(255) DEFAULT NULL,
hispaniola VARCHAR(255) DEFAULT NULL,
puertoRico VARCHAR(255) DEFAULT NULL,
virginIslands VARCHAR(255) DEFAULT NULL,
bahamas VARCHAR(255) DEFAULT NULL,
lesserAntillles VARCHAR(255) DEFAULT NULL,
editedDate VARCHAR(255) DEFAULT NULL,
data VARCHAR(255) DEFAULT NULL
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  fwi_regions_raw...";
$sql="
DROP TABLE IF EXISTS `fwi_regions_raw`;
CREATE TABLE fwi_regions_raw (
region VARCHAR(15) DEFAULT NULL,
is_country INT(1) DEFAULT 0,
notes VARCHAR(500) DEFAULT NULL,
country1 VARCHAR(255) DEFAULT NULL,
country2 VARCHAR(255) DEFAULT NULL,
country3 VARCHAR(255) DEFAULT NULL,
country4 VARCHAR(255) DEFAULT NULL,
country5 VARCHAR(255) DEFAULT NULL,
country6 VARCHAR(255) DEFAULT NULL,
country7 VARCHAR(255) DEFAULT NULL,
country8 VARCHAR(255) DEFAULT NULL,
country9 VARCHAR(255) DEFAULT NULL,
country10 VARCHAR(255) DEFAULT NULL,
country11 VARCHAR(255) DEFAULT NULL,
country12 VARCHAR(255) DEFAULT NULL,
country13 VARCHAR(255) DEFAULT NULL,
country14 VARCHAR(255) DEFAULT NULL,
country15 VARCHAR(255) DEFAULT NULL,
country16 VARCHAR(255) DEFAULT NULL,
country17 VARCHAR(255) DEFAULT NULL,
country18 VARCHAR(255) DEFAULT NULL,
country19 VARCHAR(255) DEFAULT NULL,
country20 VARCHAR(255) DEFAULT NULL,
country21 VARCHAR(255) DEFAULT NULL,
country22 VARCHAR(255) DEFAULT NULL,
country23 VARCHAR(255) DEFAULT NULL,
country24 VARCHAR(255) DEFAULT NULL,
country25 VARCHAR(255) DEFAULT NULL,
country26 VARCHAR(255) DEFAULT NULL,
UNIQUE INDEX (region),
INDEX (is_country)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  fwi_occurrences...";
$sql="
DROP TABLE IF EXISTS fwi_occurrences;
CREATE TABLE fwi_occurrences (
source_name VARCHAR(50) NOT NULL,
region VARCHAR(50) NOT NULL, 
family VARCHAR(50) DEFAULT NULL,
genus VARCHAR(50) DEFAULT NULL,
species VARCHAR(150) DEFAULT NULL,
taxon VARCHAR(250) NOT NULL,
taxon_rank VARCHAR(25) DEFAULT NULL,
status_verbatim VARCHAR(50) DEFAULT NULL,
native_status VARCHAR(50) DEFAULT NULL, 
cult_status VARCHAR(50) DEFAULT NULL, 
INDEX (source_name),
INDEX (region),
INDEX (family),
INDEX (genus),
INDEX (species),
INDEX (taxon),
INDEX (taxon_rank),
INDEX (status_verbatim),
INDEX (native_status),
INDEX (cult_status)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;


echo "  fwi_raw_temp...";
$sql="
DROP TABLE IF EXISTS fwi_raw_temp;
CREATE TABLE fwi_raw_temp (
source_name VARCHAR(50) NOT NULL,
region VARCHAR(50) NOT NULL,
country VARCHAR(50) DEFAULT NULL,
state_province VARCHAR(100) DEFAULT NULL,
county_parish VARCHAR(100) DEFAULT NULL,
family VARCHAR(50) DEFAULT NULL,
genus VARCHAR(50) DEFAULT NULL,
species VARCHAR(150) DEFAULT NULL,
taxon VARCHAR(250) NOT NULL,
taxon_rank VARCHAR(25) DEFAULT NULL,
native_status_all VARCHAR(50) DEFAULT NULL,
cult_status_all VARCHAR(50) DEFAULT NULL,
native_status VARCHAR(50) DEFAULT NULL,
cult_status VARCHAR(50) DEFAULT NULL,
INDEX (source_name),
INDEX (region),
INDEX (country),
INDEX (state_province),
INDEX (county_parish),
INDEX (family),
INDEX (genus),
INDEX (species),
INDEX (taxon),
INDEX (taxon_rank),
INDEX (native_status),
INDEX (cult_status),
INDEX (native_status_all),
INDEX (cult_status_all)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  fwi_raw_final...";
$sql="
DROP TABLE IF EXISTS fwi_raw_final;
CREATE TABLE fwi_raw_final (
id INTEGER(11) UNSIGNED NOT NULL AUTO_INCREMENT,
source_name VARCHAR(50) NOT NULL,
country VARCHAR(50) NOT NULL,
state_province VARCHAR(100) DEFAULT NULL,
county_parish VARCHAR(100) DEFAULT NULL,
family VARCHAR(50) DEFAULT NULL,
genus VARCHAR(50) DEFAULT NULL,
species VARCHAR(150) DEFAULT NULL,
taxon VARCHAR(250) NOT NULL,
taxon_rank VARCHAR(25) DEFAULT NULL,
native_status VARCHAR(50) DEFAULT NULL,
native_status_details VARCHAR(100) DEFAULT NULL,
cult_status VARCHAR(50) DEFAULT NULL,
PRIMARY KEY(id),
INDEX (source_name),
INDEX (country),
INDEX (state_province),
INDEX (county_parish),
INDEX (family),
INDEX (genus),
INDEX (species),
INDEX (taxon),
INDEX (taxon_rank),
INDEX (native_status),
INDEX (native_status_details),
INDEX (cult_status)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  fwi_country...";
$sql="
DROP TABLE IF EXISTS fwi_country;
CREATE TABLE fwi_country (
country VARCHAR(255) DEFAULT NULL,
UNIQUE INDEX (country)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  fwi_region_country...";
$sql="
DROP TABLE IF EXISTS fwi_region_country;
CREATE TABLE fwi_region_country (
region VARCHAR(15) DEFAULT NULL,
country VARCHAR(50) DEFAULT NULL,
UNIQUE INDEX region_country (region, country),
INDEX (region),
INDEX (country)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;
	
?>