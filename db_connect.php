<?php

/*
// old-style mysql connection
// use for legacy scripts until can get around to updating them
// connect to mysql
$dbh = mysqli_connect($HOST,$USERW,$PWDW,FALSE,128);
if (!$dbh) die("\r\nCould not connect to database!\r\n");

// Connect to database
$sql="USE `".$DB."`;";
sql_execute_multiple($dbh, $sql);
*/

// MYSQLI_OPT_LOCAL_INFILE required to enable LOAD LOCAL option
$dbh = mysqli_init();
mysqli_options($dbh, MYSQLI_OPT_LOCAL_INFILE, true);
mysqli_real_connect($dbh, $HOST, $USERW, $PWDW, $DB);


// Check required functions present and create them if not
include_once "check_functions.php";

?>
