<?php

/////////////////////////////////////////////////////////
// Creates generic distribution staging table, a single, 
// flattened schema into which each distribution source is 
// loaded. Once staging table has been populated, remaining
// steps to load to core database are generic
/////////////////////////////////////////////////////////

$sql="
DROP TABLE IF EXISTS distribution_staging;
CREATE TABLE distribution_staging (
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
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);