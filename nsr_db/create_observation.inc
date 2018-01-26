<?php

///////////////////////////////////////////////
// Creates new observation table in nsr
// database. Table `observation` contains
// the raw species data to be validated against
// the NSR reference database
///////////////////////////////////////////////


echo "Creating table observation...";
$sql="
DROP TABLE IF EXISTS observation;
CREATE TABLE observation (
family VARCHAR(50) DEFAULT NULL,
genus VARCHAR(50) DEFAULT NULL,
species VARCHAR(150) DEFAULT NULL,
country VARCHAR(50) DEFAULT NULL,
state_province VARCHAR(50) DEFAULT NULL,
county_parish VARCHAR(50) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci
;
";
sql_execute_multiple($sql);
echo "done";

?>



