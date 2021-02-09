<?php

////////////////////////////////////////////////
// Configuration for main write access
////////////////////////////////////////////////


$HOST = '<hostname>';
$USERW = '<write-access-user-name>';
$PWDW = '<write-access-user-password>';
// Or set to output of command to read from elsewhere. E.g., exec("cat /home/bien/config/mysql_nsr_pwd");

$DB = '<nsr-db-name>';
$DB_BATCH = $DB;	// For backward compatibility

// Reset database if in batch mode
// Parameter $MODE set at start of nsr_batch script
if ( $MODE == "batch" ) {
	$DB = $DB_BATCH;
}

?>
