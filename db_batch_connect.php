<?php

// MYSQLI_OPT_LOCAL_INFILE required to enable LOAD LOCAL option
$dbh = mysqli_init();
mysqli_options($dbh, MYSQLI_OPT_LOCAL_INFILE, true);
mysqli_real_connect($dbh, $HOST, $USERW, $PWDW, $DB_BATCH);

// Check required functions present and create them if not
include_once "check_functions.php";

?>
