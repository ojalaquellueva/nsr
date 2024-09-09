<?php

/////////////////////////////////////////////////////////////
// Import table meta from previous version of this database
/////////////////////////////////////////////////////////////

/*
Will exit with warning message if previous database or
table do not exist. Will die with error if fields in previous
table meta are not identical to field in the new table meta
*/

echo "Building table `meta` from existing table:\n";
$meta_success=TRUE;

echo "  Importing previous table `meta` from database `$META_DB_PREV`..."

// Check if the previous NSR database exists
$db_prev_exists=db_exists($META_DB_PREV, $USER, $PWD);		

if ( !$db_meta_prev_exists ) {
	echo "ERROR: previous database `$META_DB_PREV` does not exist!\n";
	$meta_success=FALSE;
} else {
	// Check if table meta existsin the previous NSR database 
	$meta_prev_exists=db_exists($dbh,'meta', $META_DB_PREV) 	

	if ( !$db_meta_prev_exists ) {
		echo "ERROR: table `meta` not found in database `$META_DB_PREV`!\n";
		$meta_success=FALSE;
	} else {
		$sql="
		DROP TABLE IF EXISTS meta_prev_raw;
		CREATE TABLE meta_prev_raw LIKE `$META_DB_PREV`.`meta`;
		INSERT INTO meta_prev_raw SELECT * FROM `$META_DB_PREV`.`meta`;
		";
		sql_execute_multiple($dbh, $sql);
		echo $done;
		
		echo "Inserting previous rows into new table...";
		$sql="
		INSERT INTO meta (
		id,
		app_version,
		db_version,
		db_version_comments,
		db_modified_date,
		db_full_build_date,
		code_version,
		code_version_comments,
		code_version_release_date,
		citation,
		publication,
		logo_path
		)
		SELECT 
		id,
		app_version,
		db_version,
		db_version_comments,
		db_modified_date,
		db_full_build_date,
		code_version,
		code_version_comments,
		code_version_release_date,
		citation,
		publication,
		logo_path
		FROM meta_prev_raw
		;
		";
		if ( !sql_execute_multiple($dbh, $sql) ) {
			echo "ERROR: Insert on table `meta` failed!\n";
			$meta_success=FALSE;
		} else {
			echo $done;
		}

	}
}

if ( !$meta_success ) {
	echo "WARNING: Insert of metadata from previous table failed. You will need to do this manually\n";
}

?>