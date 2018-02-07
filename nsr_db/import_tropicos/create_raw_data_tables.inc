<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables:\r\n";

foreach($tbl_list as $tbl) {	
	$tbl_raw = $tbl."_raw";
	
	echo "  $tbl_raw...";
	$sql="
	DROP TABLE IF EXISTS `$tbl_raw`;
	CREATE TABLE `$tbl_raw` (
	tropicos_id INTEGER(11) UNSIGNED NOT NULL,
	species VARCHAR(250) DEFAULT NULL,
	status_verbatim VARCHAR(50) DEFAULT NULL,
	PRIMARY KEY(`tropicos_id`),
	INDEX (species),
	INDEX (status_verbatim)
	)  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
	";
	sql_execute_multiple($sql);
	echo $done;
}

echo "  tropicos_raw...";
$sql="
DROP TABLE IF EXISTS `tropicos_raw`;
CREATE TABLE tropicos_raw (
id INTEGER(11) UNSIGNED NOT NULL AUTO_INCREMENT,
tropicos_id INTEGER(11) UNSIGNED DEFAULT NULL,
country VARCHAR(50) NOT NULL,
taxon_with_author VARCHAR(250) NOT NULL,
taxon VARCHAR(250) NOT NULL,
taxon_rank VARCHAR(25) DEFAULT NULL,
status_verbatim VARCHAR(50) DEFAULT NULL,
native_status VARCHAR(50) DEFAULT NULL,
cult_status VARCHAR(50) DEFAULT NULL,
PRIMARY KEY(id),
INDEX(tropicos_id),
INDEX (country),
INDEX (taxon_with_author),
INDEX (taxon),
INDEX (taxon_rank),
INDEX (status_verbatim),
INDEX (native_status),
INDEX (cult_status)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo "done";
	
?>

