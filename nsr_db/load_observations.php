<?php

///////////////////////////////////////////////////////////////////////
// Loads observation data from CSV file to table observation
///////////////////////////////////////////////////////////////////////

include "global_params.inc";

$appdir="load_observations/";

include $appdir."params.inc";

// Confirm operation
$msg_proceed="
Import raw data from file '$file_raw' to database `$DB`?
Enter 'Yes' to proceed, or 'No' to cancel: ";
$proceed=responseYesNoDie($msg_proceed);
if ($proceed===false) die("\r\nOperation cancelled\r\n");

//////////////////////////////////////////////////////////////////
// Start time and open db connection
//////////////////////////////////////////////////////////////////

// Start timer and connect to mysql
echo "\r\n********* Begin operation *********\r\n";
include $timer_on;

// connect to mysql
$dbh = mysqli_connect($HOST,$USER,$PWD,FALSE,128);
if (!$dbh) die("\r\nCould not connect to database!\r\n");

// Connect to database
$sql="USE `".$DB."`;";
sql_execute_multiple($dbh, $sql);

//////////////////////////////////////////////////////////////////
// Main script
//////////////////////////////////////////////////////////////////

include "create_observation.inc";
include $appdir."load_observation.inc";
include $appdir."index_observation.inc";
include $appdir."validate_observations.inc";


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