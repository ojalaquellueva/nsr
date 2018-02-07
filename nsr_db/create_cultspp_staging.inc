<?php

/////////////////////////////////////////////////////////
// Creates generic cultivated species staging table
/////////////////////////////////////////////////////////

// taxon_rank retained so as not to have to re-write all the
// import scripts, but not included in final table
$sql="
DROP TABLE IF EXISTS cultspp_staging;
CREATE TABLE cultspp_staging (
id INTEGER(11) UNSIGNED NOT NULL AUTO_INCREMENT,
source_name VARCHAR(50) NOT NULL,
taxon VARCHAR(250) NOT NULL,
taxon_rank VARCHAR(25) DEFAULT NULL,
is_in_db INT(1) NOT NULL DEFAULT 0,
PRIMARY KEY(id),
INDEX (source_name),
INDEX (taxon),
INDEX (taxon_rank),
INDEX (is_in_db)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci
;
";
sql_execute_multiple($sql);