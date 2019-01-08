<?php
// Open separate write connection to nsr database

include $CONFIG_DIR.'db_configw.php';

/*
$dbw2 = mysqli_connect($HOST,$USERW,$PWDW,FALSE,128);
if (!$dbw2) die("\r\nCould not connect to database!\r\n");

// Connect to database
$sql="USE `".$DB."`;";
sql_execute_multiple($dbh, $sql);
*/

// MYSQLI_OPT_LOCAL_INFILE required to enable LOAD LOCAL option
$dbw2 = mysqli_init();
mysqli_options($dbw2, MYSQLI_OPT_LOCAL_INFILE, true);
mysqli_real_connect($dbw2, $HOST, $USERW, $PWDW, $DB);

?>