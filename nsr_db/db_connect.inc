<?php

/*
//connect to database server
// the stuff after $PWD enables use of LOCAL keyword
$dbh = mysqli_connect($HOST, $USER, $PWD, false, 128) OR die("<br />Could not connect to MySQL on " . $HOST); 

//connect to db
if (!mysql_select_db($DB,$dbh)) {
	die("<br />Could not connect to '" . $DB . "' database"); 
}
*/


// MYSQLI_OPT_LOCAL_INFILE required to enable LOAD LOCAL option
$dbh = mysqli_init();
mysqli_options($dbh, MYSQLI_OPT_LOCAL_INFILE, true);
//mysqli_real_connect($dbh, $HOST, $USERW, $PWDW, $DB);
mysqli_real_connect($dbh, $HOST, $USER, $PWD, $DB);

//Set display options
$echo_on = true;	// Displays messages and sql strings for debugging
$SQL_display = true;	// Displays final SQL statement

?>