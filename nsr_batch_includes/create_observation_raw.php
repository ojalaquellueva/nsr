<?php

if ($echo_on) echo "Creating table observation_raw..."; 

$sql="
DROP TABLE IF EXISTS observation_raw;
";
sql_execute_multiple($dbh, $sql);

$sql="
CREATE TABLE observation_raw (
family VARCHAR(50) DEFAULT NULL,
genus VARCHAR(50) DEFAULT NULL,
species VARCHAR(150) DEFAULT NULL,
country VARCHAR(50) DEFAULT NULL,
state_province VARCHAR(50) DEFAULT NULL,
county_parish VARCHAR(50) DEFAULT NULL,
user_id INT(11) UNSIGNED DEFAULT NULL
);

";
sql_execute_multiple($dbh, $sql);

if ($echo_on) echo $done;

?>