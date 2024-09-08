$TEMP_TABLE_ACTION<?php

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

////////////////////////////////////////////////////
// Confirm operation 
////////////////////////////////////////////////////

$replace_db_staging = $DB_STAGING_REPLACE ? "TRUE" : "FALSE";

$msg_proceed="
Clean up Native Species Resolver (NSR) database with the following settings:
  Host: $HOSTNAME
  Database: $DB
  Drop temp tables or move to staging: $TEMP_TABLE_ACTION
  " . ($TEMP_TABLE_ACTION=='drop'?"":"Staging database: $db_staging
  Replace staging: $replace_db_staging") . "
Enter 'Yes' to proceed, or 'No' to cancel: ";
$proceed=responseYesNoDie($msg_proceed);
if ($proceed===false) die("\r\nOperation cancelled\r\n");
if ( !db_exists($DB, $USER, $PWD) ) die ("\r\nERROR: '$DB': no such database\r\n");

// Check for contradictory parameters and warn if replacing existing database
if ( $TEMP_TABLE_ACTION == "move" ) {
	$db_exists=db_exists($db_staging, $USER, $PWD);		
	$create_db_staging=TRUE;
	
	if ( $DB_STAGING_REPLACE==FALSE && $db_exists ) {
		$create_db_staging=FALSE;	
	}	

	// Warn if existing database will be deleted
	if ( $db_exists && $create_db_staging==TRUE ) {
		$msg_conf_replace_db="\r\nExisting staging database `$db_staging` will be replaced! Are you sure you want to do this? (Y/N): ";
		$REPLACE_DB=responseYesNoDie($msg_conf_replace_db);
		if ($REPLACE_DB===false) die ("\r\nOperation cancelled\r\n");
	}
}

////////////////////////////////////////////////////
// Move or drop the tables
////////////////////////////////////////////////////

// Start timer and connect to mysql
echo "\r\n********* Begin operation ********* \r\n";
include $timer_on;
$echo_on = true;		// Display messages and SQL for debugging
$SQL_display = true;	// Displays final SQL statement

if ( $TEMP_TABLE_ACTION == "move" ) {
	
	if ( $create_db_staging==TRUE ) {
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
	}
	
	include "db_connect.inc"; // Reconnect to the new DB 
	include_once "cleanup_move.inc";
} else if ( $TEMP_TABLE_ACTION == "drop" ) {
	include "db_connect.inc";
	include_once "cleanup_drop.inc";
} else if ( $TEMP_TABLE_ACTION == "none" || $TEMP_TABLE_ACTION == "nothing" ) {
	echo "No action taken (\$TEMP_TABLE_ACTION='$TEMP_TABLE_ACTION')";
} else {
	die("ERROR: Unknown option '$TEMP_TABLE_ACTION' for parameter \$TEMP_TABLE_ACTION! \n");
}

////////////////////////////////////////////////////
// Close connection and report total time elapsed 
////////////////////////////////////////////////////

mysqli_close($dbh);
include $timer_off;
$msg = "\r\nTotal time elapsed: " . $tsecs . " seconds.\r\n"; 
$msg = $msg . "********* Operation completed " . $curr_time . " *********";
if  ($echo_on) echo $msg . "\r\n\r\n"; 

//////////////////////////////////////////////////////////////////
// End script
//////////////////////////////////////////////////////////////////

?>