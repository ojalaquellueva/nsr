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

# Uncomment during development to turn on strict, verbose error-reporting
error_reporting(E_ALL & ~E_NOTICE);

//////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
// Loads results file as an asociative array
// 
// Options:
//	$filepath: path and name of file to import
//	$delim: field delimiter
////////////////////////////////////////////////////////

function file_to_array_assoc($filepath, $delim) {
	$array = $fields = array(); $i = 0;
	$handle = @fopen($filepath, "r");
	if ($handle) {
		while (($row = fgetcsv($handle, 4096, $delim , '"' , '"')) !== false) {
			// Load keys from header row & continue to next
			if (empty($fields)) {
				$fields = $row;
				continue;
			}
			
			// Load value for this row 
			foreach ($row as $k=>$value) {
				$array[$i][$fields[$k]] = $value;
			}
			$i++;
		}
		if (!feof($handle)) {
			echo "Error: unexpected fgets() fail\n";
		}
		fclose($handle);
	}
	
	return $array;
}

////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////

include "global_params.inc";
include_once $config_file;

$db_staging = $DB . "_staging"; 

// Make list of sources
$sources = "";
foreach ($src_array as $src) {
	$sources = $sources . $src . ", ";
}
$sources = substr_replace($sources, '', strlen($sources)-2,-1);

# Set SQL LIMIT statement depending on value of global
# parameter $ROW_LIMIT
$sql_limit="";
if ( ! $ROW_LIMIT=="" ) $sql_limit="LIMIT $ROW_LIMIT";

////////////////////////////////////////////////////////////
// Run preliminary checks and confirm operations and options.
// All checks are made at beginning to avoid interrupting
// execution later on.
////////////////////////////////////////////////////////////

// Prepare formatted values
$row_limit_disp=$ROW_LIMIT;
if ( $ROW_LIMIT=="" ) $row_limit_disp="[none]";
$replace_db_display=$REPLACE_DB?'Yes':'No';
$replace_db_staging = $DB_STAGING_REPLACE ? "TRUE" : "FALSE";
$meta_import_display = $META_IMPORT ? "TRUE" : "FALSE";

// Confirm operation
$msg_proceed="
Building Native Species Resolver (NSR) database with the following settings:\n
  Host: $HOSTNAME
  Database: $DB
  Replace database: $replace_db_display
  Row limit: $row_limit_disp
  Sources: $sources
  Import previous meta table: $meta_import_display" . 
  ($META_IMPORT?"\n  Previous meta table database: $META_DB_PREV":"") . "
  Drop temp tables or move to staging: $TEMP_TABLE_ACTION
  " . ($TEMP_TABLE_ACTION=='drop'?"":"Staging database: $db_staging
  Replace staging: $replace_db_staging") . "\n
Enter 'Yes' to proceed, or 'No' to cancel: ";
$proceed=responseYesNoDie($msg_proceed);
if ($proceed===false) die("\nOperation cancelled\n");

if ( db_exists($DB, $USER, $PWD) ) {
	// Confirm replacement of entire database if requested
	if ($REPLACE_DB) {
		$msg_replace_db_confirm="\nPrevious database `$DB` will be deleted! Are you sure you want to proceed? (Y/N): ";
		$replace_db_confirm=responseYesNoDie($msg_replace_db_confirm);
		if ($replace_db_confirm===false) die ("\nOperation cancelled\n");
	}
}

// Check that folder for each source is present
include_once "check_sources.inc";

// Start timer and connect to mysql
echo "\n********* Begin operation *********\n";
include $timer_on;
$echo_on = true;		// Display messages and SQL for debugging
$SQL_display = true;	// Displays final SQL statement

////////////////////////////////////////////////////////////
// Generate new empty database
////////////////////////////////////////////////////////////

if ($REPLACE_DB) {
	echo "\n#############################################\n";
	echo "Creating new database:\n\n";	
	include "mysql_connect.inc";	// Connect without specifying database
	
	// Drop and replace entire database
	echo "Creating database `$DB`...";
	$sql_create_db="
		DROP DATABASE IF EXISTS `".$DB."`;
		CREATE DATABASE `".$DB."`;
		USE `".$DB."`;
	";
	sql_execute_multiple($dbm, $sql_create_db);
	echo "done\n";
	mysqli_close($dbm);
	
	// Replace core tables
	include "db_connect.inc"; // Reconnect to the new DB 
	include_once "create_nsr_db/params.inc";
	include_once "create_nsr_db/create_tables.inc";
	echo "Populating political division tables:\n";
	include_once "create_nsr_db/populate_country.inc";
	include_once "create_nsr_db/populate_countryName.inc";
	include_once "create_nsr_db/update_country_id.inc";
	include_once "create_nsr_db/populate_state_province.inc";
	include_once "create_nsr_db/populate_state_province_name.inc";
	include_once "create_nsr_db/state_province_std.inc";
	include_once "create_nsr_db/fix_errors.inc";
	include_once "create_nsr_db/populate_gadm_admin_1_raw.inc";
	include_once "create_nsr_db/update_state_province.inc.inc";
	include_once "create_nsr_db/gf_lookup.inc";
} else {
	include "db_connect.inc";
}

// Check that required custom functions are present in target db, 
// and install them if missing. This check is essential if database 
// has been replaced
include_once "check_functions.inc";

////////////////////////////////////////////////////////////
// Load distribution data for each source
////////////////////////////////////////////////////////////
//exit("\nExiting...\n");
$src_no=1;
$src_suffix = "";
foreach ($src_array as $src) {
	echo "\n#############################################\n";
	echo "Loading source #".$src_no.": '".$src."'\n\n";	
	$src_suffix .= "_".$src;
	
	include "clear_source_params.inc";
	include_once "import_".$src."/import.php";
	include "prepare_staging/prepare_staging.php";
	include "load_core_db/load_core_db.php";	
	$src_no++;	
}

//////////////////////////////////////////////////////////////////
// Complete misc updates on core db
//////////////////////////////////////////////////////////////////

echo "\n#############################################\n";
echo "Completing final updates to core tables:\n\n";	
include_once "generic_operations/newfoundland_hack.inc";
include_once "generic_operations/standardize_ranks.inc";
include_once "generic_operations/country_sources.inc";
include_once "generic_operations/update_poldiv_source.inc";
include_once "generic_operations/taxon_country_sources.inc";
include_once "generic_operations/endemic_taxon_sources.inc";
include_once "generic_operations/optimize.inc";
if ( $META_IMPORT ) include_once "load_core_db/import_meta.inc";
include_once "load_core_db/load_meta.inc";

//////////////////////////////////////////////////////////////////
// Complete misc updates on core db
//////////////////////////////////////////////////////////////////

echo "\n#############################################\n";
echo "Setting permissions:\n\n";	
include_once "generic_operations/set_permissions.inc";

//////////////////////////////////////////////////////////////////
// Clean up temp tables, if requested
//////////////////////////////////////////////////////////////////

echo "\n#############################################\n";
echo "Cleaning up";

if ( $TEMP_TABLE_ACTION == "move" || $TEMP_TABLE_ACTION == "drop" ) {
	echo ":\n";
	include "db_connect.inc"; // Reconnect to the new DB 
	
	if ( $TEMP_TABLE_ACTION == "move" ) {
		include_once "cleanup_move.inc";
	} else {
		include_once "cleanup_drop.inc";
	}
} else if ( $TEMP_TABLE_ACTION == "none" || $TEMP_TABLE_ACTION == "nothing" ) {
	echo "...no action taken (\$TEMP_TABLE_ACTION='$TEMP_TABLE_ACTION')";
} else {
	die("...ERROR: Unknown option '$TEMP_TABLE_ACTION' for parameter \$TEMP_TABLE_ACTION! \n");
}

//////////////////////////////////////////////////////////////////
// Close connection and report total time elapsed 
//////////////////////////////////////////////////////////////////

include $timer_off;
$msg = "\nTotal time elapsed: " . $tsecs . " seconds.\n"; 
$msg = $msg . "********* Operation completed " . $curr_time . " *********";
if  ($echo_on) echo $msg . "\n\n"; 

//////////////////////////////////////////////////////////////////
// End script
//////////////////////////////////////////////////////////////////

?>