<?php

//////////////////////////////////////////////////////////////////
// Builds BIEN Native Status Resolver (NSR) reference database 
// from multiple sources 
//
// DB 'nsr' is a reference database against which one or more 
// species observations (species plus declared political
// divisions in which it was observed) are checked to assess 
// whether (a) the species is native or non-native and (b) likely
// to be a cultivated plant.
//
// These scripts build complete database or update individual sources
// in existing database, depending on options set in parameters
// file (global_params.inc).
// This is the master script; calls all others
//
// Author: Brad Boyle
// Email: bboyle@email.arizona.edu OR ojalaquellueva@gmail.com
// Date created: 18 Feb. 2014
// Latest revision date: 
//////////////////////////////////////////////////////////////////

include "global_params.inc";

include_once $config_file;

// Make list of sources
$sources = "";
foreach ($src_array as $src) {
	$sources = $sources . $src . ", ";
}
$sources = substr_replace($sources, '', strlen($sources)-2,-1);

////////////////////////////////////////////////////////////
// Run preliminary checks and confirm operations and options.
// All checks are made at beginning to avoid interrupting
// execution later on.
////////////////////////////////////////////////////////////

// Confirm basic options 
$replace_db_display=$replace_db?'Yes':'No';
$msg_proceed="
Building Native Species Resolver (NSR) database with the following settings:\r\n
  Host: $HOSTNAME
  Database: $DB
  Replace database: $replace_db_display\r\n
  Sources: $sources\r\n
Enter 'Yes' to proceed, or 'No' to cancel: ";
$proceed=responseYesNoDie($msg_proceed);
if ($proceed===false) die("\r\nOperation cancelled\r\n");

// Confirm replacement of entire database if requested
if ($replace_db) {
	$msg_conf_replace_db="\r\nPrevious database `$DB` will be deleted! Are you sure you want to proceed? (Y/N): ";
	$replace_db=responseYesNoDie($msg_conf_replace_db);
	if ($replace_db===false) die ("\r\nOperation cancelled\r\n");
}

// Check that folder for each source is present
include_once "check_sources.inc";

// Start timer and connect to mysql
echo "\r\nBegin operation\r\n";
include $timer_on;
$dbh = mysqli_connect($HOST,$USER,$PWD,FALSE,128);
if (!$dbh) die("\r\nCould not connect to database!\r\n");

////////////////////////////////////////////////////////////
// Generate new empty database
////////////////////////////////////////////////////////////

if ($replace_db) {
	echo "\r\n#############################################\r\n";
	echo "Creating new database:\r\n\r\n";	
	
	// Drop and replace entire database
	echo "Dropping previous database `$DB`...";
	$sql_create_db="
		DROP DATABASE IF EXISTS `".$DB."`;
		CREATE DATABASE `".$DB."`;
		USE `".$DB."`;
	";
	sql_execute_multiple($dbh, $sql_create_db);
	echo "done\r\n";
	
	// Replace core tables
	include_once "create_nsr_db/params.inc";
	include_once "create_nsr_db/create_tables.inc";
	include_once "create_nsr_db/populate_country.inc";
	include_once "create_nsr_db/populate_countryName.inc";
	include_once "create_nsr_db/update_country_id.inc";
	include_once "create_nsr_db/populate_state_province.inc";
	include_once "create_nsr_db/populate_state_province_name.inc";
	include_once "create_nsr_db/state_province_std.inc";
	include_once "create_nsr_db/fix_errors.inc";
	//include_once "create_nsr_db/make_cclist.inc";
	include_once "create_nsr_db/gf_lookup.inc";
}

// Re-connect to database, in case previous step skipped
$sql="USE `".$DB."`;";
sql_execute_multiple($dbh, $sql);

// Check that required custom functions are present in target db, 
// and install them if missing. This check is essential if database 
// has been replaced
include_once "check_functions.inc";

////////////////////////////////////////////////////////////
// Load distribution data for each source
////////////////////////////////////////////////////////////
//exit("\r\nExiting...\r\n");
$src_no=1;
$src_suffix = "";
foreach ($src_array as $src) {
	echo "\r\n#############################################\r\n";
	echo "Loading source #".$src_no.": '".$src."'\r\n\r\n";	
	$src_suffix .= "_".$src;
	
	include "clear_source_params.inc";
	include_once "import_".$src."/import.php";
	include "prepare_staging/prepare_staging.php";
	include "load_core_db/load_core_db.php";	
	$src_no++;	
}

//////////////////////////////////////////////////////////////////
// Complete any generic operations on core db
//////////////////////////////////////////////////////////////////

echo "\r\n#############################################\r\n";
echo "Completing general operations on core database:\r\n\r\n";	
include_once "generic_operations/newfoundland_hack.inc";
include_once "generic_operations/country_sources.inc";
include_once "generic_operations/taxon_country_sources.inc";
include_once "generic_operations/endemic_taxon_sources.inc";
include_once "generic_operations/set_permissions.inc";

// Remove any remaining temporary tables, as requested in params
include_once "cleanup_final.inc";

//////////////////////////////////////////////////////////////////
// Close connection and report total time elapsed 
//////////////////////////////////////////////////////////////////

mysqli_close($dbh);
include $timer_off;
$msg = "\r\nTotal time elapsed: " . $tsecs . " seconds.\r\n"; 
$msg = $msg . "********* Operation completed " . $curr_time . " *********";
if  ($echo_on) echo $msg . "\r\n\r\n"; 

//////////////////////////////////////////////////////////////////
// End script
//////////////////////////////////////////////////////////////////

?>