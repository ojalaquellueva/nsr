<?php

////////////////////////////////////////////////
// Adds users and permissions to final database
//
// User running this script MUST have admin-level 
// permission to do this!
// Requires array $usr_array of user names and
// attributes, set in global_params file
//
// To grant super use privileges for the user running the
// DB pipeline, including this script, log in as root and
// run the following:
// GRANT ALL PRIVILEGES ON `%`.* TO '[theuser]'@'localhost' 
// IDENTIFIED BY '[password]' WITH GRANT OPTION;
// FLUSH PRIVILEGES;
// Don't forget IDENTIFIED BY and GRANT options, 
// won't work without it
////////////////////////////////////////////////

echo "Setting permissions on completed db '$DB' for user:\r\n";

// Read-only users
foreach ($usr_array as $usr_attributes) {
	$attributes = explode('|', $usr_attributes);
	$usr = trim($attributes[0]);
	$level = trim($attributes[1]);

	echo "  '$usr'...";

	// Check if valid user name
	if ( trim($usr) == '' || stristr($usr, ' ') ) {
		echo "WARNING: not a valid user name!\r\n";
		continue;
	}

	// Check if user exists
	$sql="SELECT EXISTS (
	SELECT 1 FROM mysql.user WHERE user = '$usr'
	) AS exists_usr
	";
	$exists_usr = sql_get_first_result($dbh,  $sql, 'exists_usr' );
	if ( $exists_usr == 0 ) {
		echo "WARNING: user doesn't exist!\r\n";
		continue;
	}
	
	// Check if valid level
	$levels = array('read','write','admin');
	if ( ! in_array($level, $levels ) ) {
		echo "WARNING: access level '$level' not valid!\r\n";
		continue;
	}
	
	// Revoke existing privileges, if any
	$sql_perm = " ";	// Skipping for now, throws errors if no privileges exist

	// Assign the appropriate permissions if access level is valid
	if ( $level == 'read' ) {
		$sql_perm = $sql_perm . " 
		GRANT SELECT ON $DB.* TO '$usr'@'localhost';
		";
	} elseif ( $level == 'write' ) {
		$sql_perm = $sql_perm . " 
		GRANT SELECT, INSERT, UPDATE, DELETE, ALTER, CREATE ROUTINE
		ON $DB.* TO '$usr'@'localhost';
		GRANT EXECUTE ON $DB.* TO '$usr'@'localhost';
		GRANT DROP ON TABLE $DB.* TO '$usr'@'localhost';
		GRANT CREATE ON TABLE $DB.* TO '$usr'@'localhost';
		";	
	} elseif ( $level == 'admin' ) {
		$sql_perm = $sql_perm . " 
		GRANT ALL ON $DB.* TO '$usr'@'localhost';
		";	
	}
	
	// Update privileges table
	$sql_perm = $sql_perm . " 
	FLUSH PRIVILEGES;
	";			
	
	// Execute the final series of commands
	sql_execute_multiple($dbh, $sql_perm);
	echo $done;
}

?>