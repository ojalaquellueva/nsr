<?php

///////////////////////////////////////////////////////////////
// Populate metadata table
///////////////////////////////////////////////////////////////

echo "Loading metadata for updated database...";

// Set values
if ( $META_DB_MODIFIED_DATE == 'current' ) {
	$db_modified_date = date_create()->format('Y-m-d');
} else {
	$db_modified_date = $META_DB_MODIFIED_DATE;
}
if ( $META_DB_FULL_BUILD_DATE == 'current' ) {
	$db_full_build_date = date_create()->format('Y-m-d');
} else {
	$db_full_build_date = $META_DB_FULL_BUILD_DATE;
}
if ( $META_CODE_VERSION_RELEASE_DATE == 'current' ) {
	$code_version_release_date = date_create()->format('Y-m-d');
} else {
	$code_version_release_date = $META_CODE_VERSION_RELEASE_DATE;
}

// Insert metadata record
$sql="
INSERT INTO meta (
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
VALUES (
'$META_APP_VERSION',
'$META_DB_VERSION',
'$META_DB_VERSION_COMMENTS',
'$db_modified_date',
'$db_full_build_date',
'$META_CODE_VERSION',
'$META_CODE_VERSION_COMMENTS',
'$code_version_release_date',
'$META_CITATION',
'$META_PUBLICATION',
'$META_LOGO_PATH'
)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>