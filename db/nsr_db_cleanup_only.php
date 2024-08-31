<?php

//////////////////////////////////////////////////////////////////
// Removes temporary tables from database as separate step
//////////////////////////////////////////////////////////////////

# Uncomment during development to turn on strict, verbose error-reporting
error_reporting(E_ALL & ~E_NOTICE);

////////////////////////////////////////////////////////
// Parameters
////////////////////////////////////////////////////////

// Two option: "delete" | "move"
// delete: delete all temporary / raw tables
// move: move all temp tables to staging.
$delete_or_move= "delete"

////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////

include "global_params.inc";

include_once $config_file;

$db_staging = $DB . "_staging";

$msg_proceed="
Clean up Native Species Resolver (NSR) database with the following settings:\r\n
  Host: $HOSTNAME
  Database: $DB
  Delete or move to staging: $delete_or_move \n
  Staging database name (if applicable): $db_staging
  Sources: $sources\n
Enter 'Yes' to proceed, or 'No' to cancel: ";
$proceed=responseYesNoDie($msg_proceed);
if ($proceed===false) die("\r\nOperation cancelled\r\n");

if ( db_exists($DB, $USER, $PWD) ) {
	// Confirm replacement of entire database if requested
	if ( $delete_or_move == "move" ) {
		if ( db_exists($db_staging, $USER, $PWD) ) {
			$msg_conf_replace_db="\r\nPrevious staging database `$db_staging` will be deleted! Are you sure you want to proceed? (Y/N): ";
			$REPLACE_DB=responseYesNoDie($msg_conf_replace_db);
			if ($REPLACE_DB===false) die ("\r\nOperation cancelled\r\n");
	} else {
		die("ERROR: '$db_staging': no such database!\n";
	}
} else {
	die("ERROR: '$DB': no such database!\n";
}

// Start timer and connect to mysql
echo "\r\n********* Begin operation ********* \r\n";
include $timer_on;
$echo_on = true;		// Display messages and SQL for debugging
$SQL_display = true;	// Displays final SQL statement

////////////////////////////////////////////////////////////
// Generate new empty database
////////////////////////////////////////////////////////////

if ( $delete_or_move == "move" ) {
	echo "\r\n#############################################\r\n";
	echo "Creating new staging database:\r\n\r\n";	
	include "mysql_connect.inc";	// Connect without specifying database
	
	// Drop and replace entire database
	echo "Creating database `$db_staging`...";
	$sql_create_db="
		DROP DATABASE IF EXISTS `".$db_staging."`;
		CREATE DATABASE `".$db_staging."`;
		USE `".$db_staging."`;
	";
	sql_execute_multiple($dbm, $sql_create_db);
	echo "done\r\n";
	mysqli_close($dbm);
	
	// Replace core tables
	include "db_connect.inc"; // Reconnect to the new DB 
	include_once "cleanup_move_to_staging.inc";
} else {
	include "db_connect.inc";
	include_once "cleanup_delete.inc";
}

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