<?php

/////////////////////////////////////////////////////////
// Creates generic staging table linking a checklist
// source to a country, state or county. Enables separate
// tracking of all political divisions covered by a single
// source. Information needed for this table should be
// provided in the params file for an individual source.
// Note that poldiv_type is also the name of the table
// to which FK poldiv_id points.
// Only soure_name is loaded to staging table; id populated
// later when loading core database.
/////////////////////////////////////////////////////////

$sql="
DROP TABLE IF EXISTS poldiv_source_staging;
CREATE TABLE poldiv_source_staging (
poldiv_id INT(11) UNSIGNED NOT NULL, 
poldiv_type enum('country','state_province','county_parish') NOT NULL, 
source_name VARCHAR(50) DEFAULT NULL, 
checklist_type VARCHAR(50) DEFAULT NULL,
checklist_details VARCHAR(250) DEFAULT NULL,
INDEX (poldiv_id),
INDEX (poldiv_type),
INDEX (source_name),
INDEX (checklist_type)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($dbh, $sql);