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
taxon VARCHAR(250) NOT NULL,
taxon_rank VARCHAR(25) DEFAULT NULL,
native_status VARCHAR(50) DEFAULT NULL,
cult_status VARCHAR(50) DEFAULT NULL,
PRIMARY KEY(id),
INDEX (source_name),
INDEX (country),
INDEX (state_province),
INDEX (taxon),
INDEX (taxon_rank),
INDEX (native_status),
INDEX (cult_status)
);
";
sql_execute_multiple($dbh, $sql);