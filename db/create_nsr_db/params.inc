<?php

$tbl_country="countryName";

// Data files for political division tables
$file_country="country.csv";
$file_country_name="countryNames.txt";
$file_state_province="stateProvince.csv";
$file_state_province_name="stateProvinceName.csv";
$file_gadm_state_province="gadm_admin_1.csv";


// Include path to file in name if not in same directory as this script
$datapath=$app_dir . "create_nsr_db/data/";

// Import parameters for text file
// Needed for 'LOAD DATA INFILE' statement
// Set any variable to empty string to remove entirely
$local = " LOCAL ";	// LOCAL keyword
//$fields_terminated_by = " FIELDS TERMINATED BY ',' ";
$fields_terminated_by = " FIELDS TERMINATED BY '\t' ";
$optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  // use if text surrounded by quotes
//$optionally_enclosed_by = "";
$lines_terminated_by = " LINES TERMINATED BY '\n' ";
$ignore_lines = " IGNORE 1 LINES ";	// Ignore header line?


$fields_terminated_by_csv = " FIELDS TERMINATED BY ',' ";


?>