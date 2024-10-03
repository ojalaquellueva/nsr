<?php

///////////////////////////////////////////////////////////////
// Populate data dictionary tables
///////////////////////////////////////////////////////////////

echo "Populating data dictionary table:\n";

echo "  dd_output...";
$sql="
TRUNCATE dd_output;
INSERT INTO dd_output (col_name, ordinal_position, data_type, description)
VALUES 
('ID',1,'Positive integer','Integer idenfier (primary key) of each observation, preserves order submitted'),
('family',2,'Text','Family submitted (or inferred from genus or species)'),
('genus',3,'Text','Genus submitted (or inferred from species)'),
('species',4,'Text','Species name submitted'),
('country',5,'Text','Country of observation'),
('state_province',6,'Text','State/province of observation (optional)'),
('county_parish',7,'Text','County/parish of observation (optional)'),
('poldiv_full',8,'Text','Concatenated country:state-province:county-parish'),
('poldiv_type',9,'Text','Type of the lowest political division submitted'),
('native_status_country',10,'Text','Native status for country'),
('native_status_state_province',11,'Text','Native status for state-province'),
('native_status_county_parish',12,'Text','Native status for county-parish'),
('native_status',13,'Text','Native status within lowest political division for which checklist opinion is available'),
('native_status_reason',14,'Text','Reason native_status code was assigned'),
('native_status_sources',15,'Text','Checklist sources consulted'),
('isIntroduced',16,'Integer (0|1)','Simplified overall native status (1=introduced,  0=native, blank=status unknown)'),
('is_cultivated_taxon',17,'Integer (0|1)','Is species known to be cultivated in region of observation?  (1=cultivated,  0=wild or status unknown)')
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  dd_native_status...";
$sql="
TRUNCATE dd_native_status;
INSERT INTO dd_native_status (val, ordinal_position, description)
VALUES 
('P',1,'Present in checklist for region of observation but no explicit status assigned'),
('N',2,'Native to region of observation'),
('Ne',3,'Native and endemic to region of observation'),
('A',4,'Absent from all checklists for region of observation'),
('I',5,'Introduced, as declared in checklist for region of observation'),
('Ie',6,'Endemic to other region and therefore introduced in region of observation'),
('UNK',7,'Unknown, no checklists available for region of observation and taxon not known to be endemic elsewhere')
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>