<?php

//////////////////////////////////////////////////////////////////
// Detect rank of taxon
// Needed for parsing name from authors
// Comment out the following code if column rank already populated
//////////////////////////////////////////////////////////////////

echo "Updating table cultspp...";

$sql="
-- detect rank
UPDATE `cultspp_staging`
SET taxon_rank=
CASE
WHEN taxon LIKE '% %' THEN 'species'
ELSE 'genus'
END
;	
-- families
UPDATE `cultspp_staging`
SET taxon_rank='family'
WHERE taxon LIKE '%aceae' 
;	

-- flag species already in database
UPDATE cultspp_staging s JOIN cultspp c
ON s.taxon=c.taxon
SET s.is_in_db=1; 
";	
sql_execute_multiple($dbh, $sql);

echo $done;


?>