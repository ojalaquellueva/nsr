<?php

///////////////////////////////////////////////////////////////
// Create mysql tables identical in structure to raw text files
// And combines into single staging table
///////////////////////////////////////////////////////////////

echo "Creating raw data tables:\r\n";
// Spellings of country columns are critical for
// remaining scripts to work
echo "  $tbl_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
taxon_id BIGINT,
taxon VARCHAR(250),
dist_string VARCHAR(250),
link VARCHAR(250),
taxon_matched VARCHAR(250),
status VARCHAR(250),
Argentina VARCHAR(250),
Chile VARCHAR(250),
Paraguay VARCHAR(250),
Uruguay VARCHAR(250),
Brazil VARCHAR(250),
updated VARCHAR(250)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Index the tables
ALTER TABLE $tbl_raw
ADD INDEX (taxon_id),
ADD INDEX (taxon),
ADD INDEX (taxon_matched),
ADD INDEX (status),
ADD INDEX (Argentina),
ADD INDEX (Chile),
ADD INDEX (Paraguay),
ADD INDEX (Uruguay),
ADD INDEX (Brazil)
; 
";
sql_execute_multiple($dbh, $sql);
echo $done;
	
?>