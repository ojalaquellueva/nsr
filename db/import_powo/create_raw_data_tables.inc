<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables\r\n";

echo "  `$tbl_names_raw`...";
$sql="
DROP TABLE IF EXISTS $tbl_names_raw;
CREATE TABLE $tbl_names_raw (
`plant_name_id` VARCHAR(50) DEFAULT NULL,
`ipni_id` VARCHAR(50) DEFAULT NULL,
`taxon_rank` VARCHAR(50) DEFAULT NULL,
`taxon_status` VARCHAR(50) DEFAULT NULL,
`family` VARCHAR(50) DEFAULT NULL,
`genus_hybrid` VARCHAR(50) DEFAULT NULL,
`genus` VARCHAR(50) DEFAULT NULL,
`species_hybrid` VARCHAR(50) DEFAULT NULL,
`species` VARCHAR(50) DEFAULT NULL,
`infraspecific_rank` VARCHAR(50) DEFAULT NULL,
`infraspecies` VARCHAR(50) DEFAULT NULL,
`parenthetical_author` VARCHAR(50) DEFAULT NULL,
`primary_author` VARCHAR(50) DEFAULT NULL,
`publication_author` VARCHAR(50) DEFAULT NULL,
`place_of_publication` VARCHAR(150) DEFAULT NULL,
`volume_and_page` VARCHAR(50) DEFAULT NULL,
`first_published` VARCHAR(50) DEFAULT NULL,
`nomenclatural_remarks` VARCHAR(250) DEFAULT NULL,
`geographic_area` VARCHAR(100) DEFAULT NULL,
`lifeform_description` VARCHAR(100) DEFAULT NULL,
`climate_description` VARCHAR(100) DEFAULT NULL,
`taxon_name` VARCHAR(100) DEFAULT NULL,
`taxon_authors` VARCHAR(150) DEFAULT NULL,
`accepted_plant_name_id` VARCHAR(50) DEFAULT NULL,
`basionym_plant_name_id` VARCHAR(50) DEFAULT NULL,
`replaced_synonym_author` VARCHAR(150) DEFAULT NULL,
`homotypic_synonym` VARCHAR(50) DEFAULT NULL,
`parent_plant_name_id` VARCHAR(50) DEFAULT NULL,
`powo_id` VARCHAR(150) DEFAULT NULL,
`hybrid_formula` VARCHAR(50) DEFAULT NULL,
`reviewed` VARCHAR(50) DEFAULT NULL
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  `$tbl_dist_raw`...";
$sql="
DROP TABLE IF EXISTS $tbl_dist_raw;
CREATE TABLE $tbl_dist_raw (
`plant_locality_id` VARCHAR(150) DEFAULT NULL,
`plant_name_id` VARCHAR(150) DEFAULT NULL,
`continent_code_l1` VARCHAR(50) DEFAULT NULL,
`continent` VARCHAR(150) DEFAULT NULL,
`region_code_l2` VARCHAR(50) DEFAULT NULL,
`region` VARCHAR(150) DEFAULT NULL,
`tdwgCodeL3` VARCHAR(50) DEFAULT NULL,
`area` VARCHAR(150) DEFAULT NULL,
`introduced` TINYINT DEFAULT NULL,
`extinct` TINYINT DEFAULT NULL,
`location_doubtful` TINYINT DEFAULT NULL
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

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