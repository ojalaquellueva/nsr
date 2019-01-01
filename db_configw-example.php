<?php

/////////////////////////////////////////////////////
// Example write access database configuration file
// Place actual file outside application directory 
// and rename to db_configw.php
/////////////////////////////////////////////////////

$HOST = 'host-name';
$USERW = 'write-access-user-name';
$PWDW = 'write-access-pwd';

// NSR database used by web service
$DB = 'nsr-mysql-database-name';

// NSR database used by batch application
// Can be same or different from web service
// database
$DB_BATCH = "nsr-batch-database-name";

// Reset database if in batch mode
// Parameter $MODE set at start of nsr_batch script
if ( $MODE == "batch" ) {
	$DB = $DB_BATCH;
}

?>