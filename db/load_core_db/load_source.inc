<?php
// Checks if source for names being added is already in table `source`; if not, adds new record
// Also determines source for default synonymy and classification

if ($echo_on) echo "  Loading source information...";
$sql="SELECT COUNT(*) AS sources FROM `source` WHERE `source_name`='$source_name';";
$records=sql_get_first_result($dbh, $sql,'sources');
If ($records===false) {
	echo "ERROR: Offending SQL:\r\n$sql\r\n";
	echo "Records=".$records."\r\n";
	die("failed query on table `source`");
}
	
if ($records>1) {
	// > 1 entry for this source; issue warning and quit
	die("Warning: >1 entry for `source_name`='$source_name' in table `source`");
} else {	

	if ($records==0) {		
		// Add new record for this source
		$sql="INSERT INTO `source`(
			source_name,
			source_name_full,
			source_url,
			citation,
			source_contact_name,
			source_contact_email,
			date_accessed,
			is_comprehensive,
			regional_scope,
			taxonomic_scope
			)
			SELECT
			'$source_name',
			'$source_name_full',
			'$source_url',
			'$citation',
			'$source_contact_name',
			'$source_contact_email',
			'$date_accessed',
			$is_comprehensive,
			'$regional_scope',
			'$taxonomic_scope'
			;
			";
		$msg_error="Failed to insert new record for source_name='$source_name' in table `source`!\r\n";
	} else {
		// update existing record for this source
		$sql="
			UPDATE source
			SET
			source_name_full='$source_name_full',
			source_url='$source_url',
			citation='$citation',
			source_contact_name='$source_contact_name',
			source_contact_email='$source_contact_email',
			date_accessed='$date_accessed',
			is_comprehensive=$is_comprehensive,
			regional_scope='$regional_scope',
			taxonomic_scope='$taxonomic_scope'
			WHERE `source_name`='$source_name';
		";
		$msg_error="Failed to update existing record for source_name='$source_name' in table `source`!\r\n";
	}
	
	// Execute the SQL selected
	if (sql_execute($dbh,$sql,TRUE,$echo_on,"",$msg_error));
}
echo $msg_success;

// Update citation for this source from citation staging table
// This table will exist if source citation was loaded from bibtex file
if ( isset($citation_from_bibtex) ) {
	if ( $citation_from_bibtex==TRUE ) {
		echo "  Updating citation for source `$src` from table `source_citation_staging`...";
		$sql="
		Update source a JOIN source_citation_staging b
		ON a.source_name=b.source_name
		SET a.citation=b.citation
		;
		";
		sql_execute_multiple($dbh, $sql); 
		echo $done;
		
		echo "  Dropping table `source_citation_staging`...";
		$sql="
		ALTER TABLE source_citation_staging 
		RENAME TO source_citation_staging_". $src . ";"
		;
		sql_execute_multiple($dbh, $sql); 
		echo $done;
	}
}

// Get ID for current source
$sql="SELECT source_id FROM `source` WHERE `source_name`='$source_name'";
$source_id=sql_get_first_result($dbh, $sql,'source_id');
If ($source_id===false or $source_id==NULL) die("failed to retrieve 'source_id' from table `source`");

?>
