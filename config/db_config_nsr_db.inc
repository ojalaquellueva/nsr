<?php

///////////////////////////////////////////////////////////////
// DB connection parameters for initial build of NSR DB only
///////////////////////////////////////////////////////////////

$HOST = "localhost";
// Explicit host name for display at runtime
$HOST=="localhost"?$HOSTNAME=exec('hostname -f'):$HOSTNAME=$HOST;
$USER = "<db-build-user-name>";
$PWD = "db-build-user-pwd";
$DB = "<nsr-db-name>";

?>
