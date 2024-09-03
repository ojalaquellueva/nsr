<?php

//////////////////////////////////////////////////////////////////
// Removes temporary tables from database as separate step
//////////////////////////////////////////////////////////////////

# Uncomment during development to turn on strict, verbose error-reporting
error_reporting(E_ALL & ~E_NOTICE);

////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////

include "global_params.inc";

include_once $config_file;

$db_staging = $DB . "_staging";

$msg_proceed="
Clean up Native Species Resolver (NSR) database with the following settings:
  Host: $HOSTNAME
  Database: $DB
  Drop temp tables or move to staging: $DROP_OR_MOVE
  Staging database name (if applicable): $db_staging
Enter 'Yes' to proceed, or 'No' to cancel: ";
$proceed=responseYesNoDie($msg_proceed);
if ($proceed===false) die("\r\nOperation cancelled\r\n");

if ( db_exists($DB, $USER, $PWD) ) {
	// Confirm replacement of entire database if requested
	if ( $DROP_OR_MOVE == "move" ) {
		if ( db_exists($db_staging, $USER, $PWD) ) {
			$msg_conf_replace_db="\r\nPrevious staging database `$db_staging` will be deleted! Are you sure you want to proceed? (Y/N): ";
			$REPLACE_DB=responseYesNoDie($msg_conf_replace_db);
			if ($REPLACE_DB===false) die ("\r\nOperation cancelled\r\n");
		}
	}
} else {
	die("ERROR: '$DB': no such database!\n");
}

// Start timer and connect to mysql
echo "\r\n********* Begin operation ********* \r\n";
include $timer_on;
$echo_on = true;		// Display messages and SQL for debugging
$SQL_display = true;	// Displays final SQL statement

if ( $DROP_OR_MOVE == "move" ) {
	echo "Creating staging database:\r\n\r\n";	
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
	include_once "cleanup_move.inc";
} else if ( $DROP_OR_MOVE == "drop" ) {
	include "db_connect.inc";
	include_once "cleanup_drop.inc";
} else if ( $DROP_OR_MOVE == "neither" ) {
	echo "No action taken (\$DROP_OR_MOVE='neither')";
} else {
	die("ERROR: Unknown option '$DROP_OR_MOVE' for parameter \$DROP_OR_MOVE! \n");
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