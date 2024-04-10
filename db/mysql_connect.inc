<?php

///////////////////////////////////////////////
// Connect to MySQL without specifying database
///////////////////////////////////////////////

// MYSQLI_OPT_LOCAL_INFILE required to enable LOAD LOCAL option
$dbm = mysqli_init();
mysqli_options($dbm, MYSQLI_OPT_LOCAL_INFILE, true);
//mysqli_real_connect($dbh, $HOST, $USERW, $PWDW, $DB);
mysqli_real_connect($dbm, $HOST, $USER, $PWD);

?>