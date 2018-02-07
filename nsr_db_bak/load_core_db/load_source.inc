<?php
// Checks if source for names being added is already in table `source`; if not, adds new record
// Also determines source for default synonymy and classification

if ($echo_on) echo "  Updating source information...";
$sql="SELECT COUNT(*) AS sources FROM `source` WHERE `source_name`='$source_name';";
$records=sql_get_first_result($sql,'sources');
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
		$sql_source="INSERT INTO `source`(
			source_name,
			source_name_full,
			source_url,
			source_citation,
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
			'$source_citation',
			'$source_contact_name',
			'$source_contact_email',
			'$date_accessed',
			$is_comprehensive,
			'$regional_scope',
			'$taxonomic_scope'
			;
			";
		$msg_error="Failed to insert new record for source_name='$source_name' in table `source`!\r\n";
		if (sql_execute($sql_source,TRUE,$echo_on,"",$msg_error));
	} else {
		// update existing record for this source
		$sql="
			UPDATE source
			SET
			source_name_full='$source_name_full',
			source_url='$source_url',
			source_citation='$source_citation',
			source_contact_name='$source_contact_name',
			source_contact_email='$source_contact_email',
			date_accessed='$date_accessed',
			is_comprehensive=$is_comprehensive,
			regional_scope='$regional_scope',
			taxonomic_scope='$taxonomic_scope'
			WHERE `source_name`='$source_name';
		";
	}
}
echo $msg_success;

// Get ID for current source
$sql="SELECT source_id FROM `source` WHERE `source_name`='$source_name'";
$source_id=sql_get_first_result($sql,'source_id');
If ($source_id===false or $source_id==NULL) die("failed retrieve 'source_id' from table `source`");
//echo "    Currently loading source='$source_name' (source ID=$source_id)\r\n";

?>
