<?php
///////////////////////////////////////
//connect to database server
///////////////////////////////////////

// MYSQLI_OPT_LOCAL_INFILE required to enable LOAD LOCAL option
$dbh = mysqli_init();
mysqli_options($dbh, MYSQLI_OPT_LOCAL_INFILE, true);
//mysqli_real_connect($dbh, $HOST, $USERW, $PWDW, $DB);
mysqli_real_connect($dbh, $HOST, $USER, $PWD, $DB);

?>