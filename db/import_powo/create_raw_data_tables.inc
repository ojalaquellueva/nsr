<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables\r\n";

$tbl_raw=$src."_raw";
echo "  `$tbl_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
fqId VARCHAR(250) DEFAULT NULL,
query VARCHAR(250) DEFAULT NULL,
modified VARCHAR(250) DEFAULT NULL,
bibliographicCitation VARCHAR(1000) DEFAULT NULL,
genus VARCHAR(250) DEFAULT NULL,
taxonomicStatus VARCHAR(250) DEFAULT NULL,
kingdom VARCHAR(250) DEFAULT NULL,
phylum VARCHAR(250) DEFAULT NULL,
family VARCHAR(250) DEFAULT NULL,
source VARCHAR(250) DEFAULT NULL,
namePublishedInYear VARCHAR(250) DEFAULT NULL,
name VARCHAR(250) DEFAULT NULL,
authors VARCHAR(250) DEFAULT NULL,
species VARCHAR(250) DEFAULT NULL,
`rank` VARCHAR(250) DEFAULT NULL,
reference VARCHAR(250) DEFAULT NULL,
accepted_fqId VARCHAR(250) DEFAULT NULL,
accepted_name VARCHAR(250) DEFAULT NULL,
accepted_author VARCHAR(250) DEFAULT NULL,
accepted_rank VARCHAR(250) DEFAULT NULL,
accepted_taxonomicStatus VARCHAR(250) DEFAULT NULL,
establishment VARCHAR(250) DEFAULT NULL,
featureId VARCHAR(250) DEFAULT NULL,
tdwgCode VARCHAR(250) DEFAULT NULL,
tdwgLevel VARCHAR(250) DEFAULT NULL,
area_name VARCHAR(500) DEFAULT NULL,
infraspecies VARCHAR(250) DEFAULT NULL,
occurrenceStatus VARCHAR(250) DEFAULT NULL,
threatStatus VARCHAR(250) DEFAULT NULL
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

$tbl_region_codes=$src."_region_codes";
echo "  `$tbl_region_codes`...";
$sql="
DROP TABLE IF EXISTS `$tbl_region_codes`;
CREATE TABLE $tbl_region_codes (
seq INT(11) NOT NULL,
code VARCHAR(250),
code_type VARCHAR(50),
region VARCHAR(500),
alt_region VARCHAR(500),
country VARCHAR(250),
state_province VARCHAR(250),
warning VARCHAR(500),
notes VARCHAR(250),
INDEX(code),
INDEX(region)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

$tbl_poldivs = $src . "_poldivs";
echo "  `$tbl_poldivs`...";
$sql="
DROP TABLE IF EXISTS $tbl_poldivs;
CREATE TABLE $tbl_poldivs (
user_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
country_verbatim VARCHAR(250) DEFAULT NULL,
state_province_verbatim VARCHAR(250) DEFAULT NULL,
county_parish_verbatim VARCHAR(250) DEFAULT NULL,
PRIMARY KEY (user_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

$tbl_poldivs_scrubbed = $src . "_poldivs_gnrs";
echo "  `$tbl_poldivs_scrubbed`...";
$sql="
DROP TABLE IF EXISTS $tbl_poldivs_scrubbed;
CREATE TABLE $tbl_poldivs_scrubbed (
poldiv_full_verbatim VARCHAR(750) DEFAULT NULL,
country_verbatim VARCHAR(250) DEFAULT NULL,
state_province_verbatim VARCHAR(250) DEFAULT NULL,
county_parish_verbatim VARCHAR(250) DEFAULT NULL,
poldiv_full VARCHAR(750) DEFAULT NULL,
country VARCHAR(250) DEFAULT NULL,
state_province VARCHAR(250) DEFAULT NULL,
county_parish VARCHAR(250) DEFAULT NULL,
country_id VARCHAR(250) DEFAULT NULL,
state_province_id VARCHAR(250) DEFAULT NULL,
county_parish_id VARCHAR(250) DEFAULT NULL,
match_method_country VARCHAR(250) DEFAULT NULL,
match_method_state_province VARCHAR(250) DEFAULT NULL,
match_method_county_parish VARCHAR(250) DEFAULT NULL,
match_score_country VARCHAR(250) DEFAULT NULL,
match_score_state_province VARCHAR(250) DEFAULT NULL,
match_score_county_parish VARCHAR(250) DEFAULT NULL,
poldiv_submitted VARCHAR(250) DEFAULT NULL,
poldiv_matched VARCHAR(250) DEFAULT NULL,
match_status VARCHAR(250) DEFAULT NULL,
user_id VARCHAR(250) DEFAULT NULL,
country_iso VARCHAR(250) DEFAULT NULL,
state_province_iso VARCHAR(250) DEFAULT NULL,
county_parish_iso VARCHAR(250) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>