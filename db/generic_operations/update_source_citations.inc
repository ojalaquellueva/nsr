<?php

////////////////////////////////////////////////////
// Update citation information for sources for which
// a bibtex file is available. Add more source-specific
// code blocks as needed.
// This method is hardwired but simple. Eventually
// should be added to the import pipeline of each
// source using a more generic approach.
/////////////////////////////////////////////////////

echo "Updating source citations from bibtex files:\n";

$citation_data_dir_base="/home/boyle/bien/nsr/data/db/";

$curr_src="newguinea";
$src_data_dir=$curr_src."/";
$bibfile=$curr_src.".bib.no-line-endings";
echo "  $curr_src...";
$sql="
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Dummy dos line endings used to trick into loading as single row
LOAD DATA LOCAL INFILE '".$citation_data_dir_base.$src_data_dir.$bibfile."' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.source_name='$curr_src'
;
DROP TABLE IF EXISTS citation_raw;
";
sql_execute_multiple($dbh, $sql);
echo $done;

$curr_src="fwi";
$src_data_dir=$curr_src."/";
$bibfile=$curr_src.".bib.no-line-endings";
echo "  $curr_src...";
$sql="
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Dummy dos line endings used to trick into loading as single row
LOAD DATA LOCAL INFILE '".$citation_data_dir_base.$src_data_dir.$bibfile."' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.source_name='$curr_src'
;
DROP TABLE IF EXISTS citation_raw;
";
sql_execute_multiple($dbh, $sql);
echo $done;

$curr_src="flbr";
$src_data_dir=$curr_src."/";
$bibfile=$curr_src.".bib.no-line-endings";
echo "  $curr_src...";
$sql="
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Dummy dos line endings used to trick into loading as single row
LOAD DATA LOCAL INFILE '".$citation_data_dir_base.$src_data_dir.$bibfile."' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.source_name='$curr_src'
;
DROP TABLE IF EXISTS citation_raw;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>