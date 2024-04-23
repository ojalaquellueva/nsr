<?php

echo "Creating tables...";
$sql="
DROP TABLE IF EXISTS meta;
CREATE TABLE meta (
id int unsigned auto_increment,
app_version VARCHAR(50) DEFAULT NULL,
db_version VARCHAR(50) DEFAULT NULL,
db_version_comments VARCHAR(250) DEFAULT NULL,
db_modified_date date,
db_full_build_date date,
code_version VARCHAR(50) DEFAULT NULL,
code_version_comments VARCHAR(250) DEFAULT NULL,
code_version_release_date date,
citation text,
publication text,
logo_path text,
PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
;

DROP TABLE IF EXISTS source;
CREATE TABLE source (
source_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
source_name VARCHAR(50) NOT NULL,
source_name_full VARCHAR(250) NOT NULL,
source_url VARCHAR(500) DEFAULT NULL,
source_citation TEXT,
source_contact_name VARCHAR(50) DEFAULT NULL,
source_contact_email VARCHAR(250) DEFAULT NULL,
date_accessed VARCHAR(10) DEFAULT NULL,
is_comprehensive INT(1) DEFAULT NULL,
regional_scope VARCHAR(50) DEFAULT 'country',
taxonomic_scope VARCHAR(250) DEFAULT NULL,
PRIMARY KEY (source_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

DROP TABLE IF EXISTS distribution;
CREATE TABLE distribution (
distribution_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
source_id INT(11) UNSIGNED NOT NULL,
taxon_rank VARCHAR(25) NOT NULL,
taxon VARCHAR(150) NOT NULL,
country VARCHAR(50) NOT NULL,
state_province VARCHAR(100) DEFAULT NULL,
state_province_full VARCHAR(150) DEFAULT NULL,
county_parish VARCHAR(100) DEFAULT NULL,
county_parish_full VARCHAR(250) DEFAULT NULL,
poldiv_full VARCHAR(250) DEFAULT NULL,
poldiv_type VARCHAR(25) DEFAULT NULL,
native_status VARCHAR(50) DEFAULT NULL,
native_status_details VARCHAR(100) DEFAULT NULL, 
cult_status VARCHAR(50) DEFAULT NULL,
is_cultivated_taxon INT(1) DEFAULT 0, 
PRIMARY KEY(distribution_id),
FOREIGN KEY (source_id) REFERENCES source(source_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

DROP TABLE IF EXISTS cclist;
CREATE TABLE cclist (
country VARCHAR(100) NOT NULL,
state_province VARCHAR(100) DEFAULT '',
county_parish VARCHAR(100) DEFAULT '',
INDEX (country),
INDEX (state_province),
INDEX (county_parish)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

DROP TABLE IF EXISTS country;
CREATE TABLE country (
country_id INT(11) UNSIGNED NOT NULL, 
country VARCHAR(100) NOT NULL,
country_iso VARCHAR(2) NOT NULL,
country_iso_alpha3 VARCHAR(3) DEFAULT NULL,
country_fips VARCHAR(50) DEFAULT NULL,
PRIMARY KEY (country_id),
INDEX (country),
INDEX (country_iso),
INDEX (country_iso_alpha3),
INDEX (country_fips)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- poldiv type is also the name of the table
-- to which FK poldiv_id points
DROP TABLE IF EXISTS poldiv_source;
CREATE TABLE poldiv_source (
poldiv_source_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT,  
poldiv_id INT(11) UNSIGNED NOT NULL, 
poldiv_name VARCHAR(100) DEFAULT NULL,
poldiv_type enum('country','state_province','county_parish') NOT NULL, 
gid_0 VARCHAR(12) DEFAULT NULL,
gid_1 VARCHAR(12) DEFAULT NULL,
gid_2 VARCHAR(12) DEFAULT NULL,
country VARCHAR(100) DEFAULT NULL,
state_province VARCHAR(150) DEFAULT NULL,
county_parish VARCHAR(150) DEFAULT NULL,
source_id INT(11) UNSIGNED NOT NULL, 
checklist_type VARCHAR(50) DEFAULT NULL,
checklist_details VARCHAR(250) DEFAULT NULL,
PRIMARY KEY (poldiv_source_id),
INDEX (poldiv_id),
INDEX (gid_0),
INDEX (gid_1),
INDEX (gid_2),
INDEX (country),
INDEX (poldiv_type),
INDEX (poldiv_name),
INDEX (source_id),
INDEX (checklist_type)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


DROP TABLE IF EXISTS countryName;
CREATE TABLE countryName (
countryNameID INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
countryName VARCHAR(100) DEFAULT NULL,
countryID INT(11) UNSIGNED DEFAULT NULL,
isoCode VARCHAR(2) DEFAULT NULL,
countryCode3Char VARCHAR(3) DEFAULT NULL,
countryNameStd VARCHAR(100) DEFAULT NULL,
isNewWorld INT(1) DEFAULT 0,
PRIMARY KEY (countryNameID),
INDEX (countryName),
INDEX (countryID),
INDEX (isoCode),
INDEX (countryCode3Char),
INDEX (countryNameStd),
INDEX (isNewWorld)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

DROP TABLE IF EXISTS state_province;
CREATE TABLE state_province (
state_province_id INT(11) UNSIGNED NOT NULL PRIMARY KEY, 
country VARCHAR(100) DEFAULT NULL, 
country_iso VARCHAR(5) DEFAULT NULL, 
state_province VARCHAR(100) DEFAULT NULL, 
state_province_ascii VARCHAR(100) DEFAULT NULL, 
state_province_code VARCHAR(25) DEFAULT NULL, 
state_province_code_unique VARCHAR(52) DEFAULT NULL,
INDEX (country),
INDEX (country_iso),
INDEX (state_province),
INDEX (state_province_ascii),
INDEX (state_province_code),
INDEX (state_province_code_unique)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

DROP TABLE IF EXISTS state_province_name;
CREATE TABLE state_province_name (
state_province_name_id INT(11) UNSIGNED NOT NULL PRIMARY KEY, 
state_province_name VARCHAR(100) DEFAULT NULL, 
country_iso VARCHAR(5) DEFAULT NULL, 
country VARCHAR(100) DEFAULT NULL, 
state_province_id INT(11) UNSIGNED DEFAULT NULL, 
state_province VARCHAR(100) DEFAULT NULL, 
state_province_ascii VARCHAR(100) DEFAULT NULL,
INDEX (state_province_name),
INDEX (country_iso),
INDEX (country),
INDEX (state_province_id),
INDEX (state_province),
INDEX (state_province_ascii)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

DROP TABLE IF EXISTS cultspp;
CREATE TABLE cultspp (
cultspp_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
source_id INT(11) UNSIGNED NOT NULL,
taxon VARCHAR(150) NOT NULL,
PRIMARY KEY(cultspp_id),
INDEX(taxon),
FOREIGN KEY (source_id) REFERENCES source(source_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

DROP TABLE IF EXISTS cache;
CREATE TABLE cache (
id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
family VARCHAR(50) DEFAULT NULL,
genus VARCHAR(50) DEFAULT NULL,
species VARCHAR(150) DEFAULT NULL,
country VARCHAR(50) DEFAULT NULL,
state_province VARCHAR(100) DEFAULT NULL,
state_province_full VARCHAR(150) DEFAULT NULL,
county_parish VARCHAR(100) DEFAULT NULL,
county_parish_full VARCHAR(250) DEFAULT NULL,
poldiv_full VARCHAR(250) DEFAULT NULL,
poldiv_type VARCHAR(25) DEFAULT NULL,
native_status_country VARCHAR(25) DEFAULT NULL,
native_status_state_province VARCHAR(25) DEFAULT NULL,
native_status_county_parish VARCHAR(25) DEFAULT NULL,
native_status VARCHAR(25) DEFAULT NULL,
native_status_reason VARCHAR(250) DEFAULT NULL,
native_status_sources VARCHAR(250) DEFAULT NULL,
isIntroduced INT(1) DEFAULT NULL,
isCultivatedNSR INT(1) DEFAULT 0,
is_cultivated_taxon INT(1) DEFAULT 0, 
PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
;

-- User-submitted observations plus NSR resolution results
DROP TABLE IF EXISTS observation;
CREATE TABLE observation (
id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
job VARCHAR(500) NOT NULL, 
batch INT(11) UNSIGNED DEFAULT NULL,
family VARCHAR(50) DEFAULT NULL,
genus VARCHAR(50) DEFAULT NULL,
species VARCHAR(150) DEFAULT NULL,
country VARCHAR(50) NOT NULL,
state_province VARCHAR(100) DEFAULT NULL,
state_province_full VARCHAR(150) DEFAULT NULL,
county_parish VARCHAR(100) DEFAULT NULL,
county_parish_full VARCHAR(250) DEFAULT NULL,
poldiv_full VARCHAR(250) DEFAULT NULL,
poldiv_type VARCHAR(25) DEFAULT NULL,
native_status_country VARCHAR(25) DEFAULT NULL,
native_status_state_province VARCHAR(25) DEFAULT NULL,
native_status_county_parish VARCHAR(25) DEFAULT NULL,
native_status VARCHAR(25) DEFAULT NULL,
native_status_reason VARCHAR(250) DEFAULT NULL,
native_status_sources VARCHAR(250) DEFAULT NULL,
isIntroduced INT(1) DEFAULT NULL,
isCultivatedNSR INT(1) UNSIGNED DEFAULT 0,
is_cultivated_taxon INT(1) UNSIGNED DEFAULT 0,
is_in_cache INT(11) UNSIGNED DEFAULT 0,
user_id INT(11) UNSIGNED DEFAULT NULL,
PRIMARY KEY (id)
);

-- Lookup of family for a genus
-- Indexes added after loading
DROP TABLE IF EXISTS gf_lookup;
CREATE TABLE gf_lookup (
gf_lookup_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
genus VARCHAR(100) NOT NULL,
family VARCHAR(100) NOT NULL,
source VARCHAR(150) NOT NULL,
PRIMARY KEY(gf_lookup_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
;

";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Indexing tables...";
$sql="
ALTER TABLE source
ADD INDEX (source_name),
ADD INDEX (is_comprehensive),
ADD INDEX (regional_scope),
ADD INDEX (taxonomic_scope)
;

ALTER TABLE distribution
ADD INDEX (taxon_rank),
ADD INDEX (taxon),
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish),
ADD INDEX (native_status),
ADD INDEX (cult_status),
ADD INDEX (is_cultivated_taxon)
;

ALTER TABLE cache
ADD INDEX (family),
ADD INDEX (genus),
ADD INDEX (species),
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish),
ADD INDEX (state_province_full),
ADD INDEX (county_parish_full),
ADD INDEX (poldiv_full),
ADD INDEX (poldiv_type)
;

ALTER TABLE observation
ADD INDEX (job),
ADD INDEX (batch),
ADD INDEX (family),
ADD INDEX (genus),
ADD INDEX (species),
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish),
ADD INDEX (state_province_full),
ADD INDEX (county_parish_full),
ADD INDEX (poldiv_full),
ADD INDEX (poldiv_type),
ADD INDEX (native_status_country),
ADD INDEX (native_status_state_province),
ADD INDEX (native_status_county_parish),
ADD INDEX (native_status),
ADD INDEX (native_status_reason),
ADD INDEX (native_status_sources),
ADD INDEX (isIntroduced),
ADD INDEX (isCultivatedNSR),
ADD INDEX (is_cultivated_taxon),
ADD INDEX (is_in_cache)
;

";
sql_execute_multiple($dbh, $sql);
echo $done;


?>