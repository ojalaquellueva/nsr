<?php
// Open separate write connection to nsr database

include $CONFIG_DIR.'db_configw.php';
$dbw2 = mysql_connect($HOST,$USERW,$PWDW,FALSE,128);
if (!$dbw2) die("\r\nCould not connect to database!\r\n");

// Connect to database
$sql="USE `".$DB."`;";
sql_execute_multiple($sql);

?>