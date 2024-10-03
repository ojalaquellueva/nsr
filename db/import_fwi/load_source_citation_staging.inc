<?php

////////////////////////////////////////////////////
// Load citation information for sources for which
// a bibtex file is available.
// Imports citation from bibtex file into table 
// source_citation_staging.  
/////////////////////////////////////////////////////

echo "Loading source citation from bibtex file:\n";

////////////////////////////////////////////////
// Parameters
////////////////////////////////////////////////

# bibtex file names
$bibfile_basename=$src;
$bibfile_raw_name = $bibfile_basename . ".bib";
$bibfile_final_name = $bibfile_raw_name . ".no-line-endings";

// Raw bibtext file, possibly with line endings
$bibfile_raw = $datapath . $bibfile_raw_name;

// Final bibtex file, line endings removed
$bibfile_final = $datapath . $bibfile_final_name;

////////////////////////////////////////////////
// Main
////////////////////////////////////////////////

echo "  Preparing bibtex file...";
// Remove line endings from raw bibtex
$cmd="sed 's/\s\s*/ /g' ".$bibfile_raw." > ".$bibfile_final ;	
exec($cmd, $output, $status);
if ( $status ) die("ERROR sed command #1!\n");
$cmd="sed -i ':a;N;$!ba;s/\\n/ /g' ".$bibfile_final ;  // Note extra escape: "\\n"
exec($cmd, $output, $status);
if ( $status ) die("ERROR sed command #2!\n");
echo $done;

echo "  Importing bibtex file...";
// Import the final bibtex
$sql="
DROP TABLE IF EXISTS source_citation_staging;
CREATE TABLE source_citation_staging (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Dummy dos line endings used to trick into loading as single row
LOAD DATA LOCAL INFILE '".$bibfile_final."' 
INTO TABLE source_citation_staging 
LINES TERMINATED BY '\r'
;
ALTER TABLE source_citation_staging
ADD COLUMN source_name VARCHAR(50) DEFAULT NULL
; 
UPDATE source_citation_staging
SET source_name='$src'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>