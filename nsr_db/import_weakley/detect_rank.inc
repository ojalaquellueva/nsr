<?php

//////////////////////////////////////////////////////////////////
// Detect rank of taxon
// Needed for parsing name from authors
// Comment out the following code if column rank already populated
//////////////////////////////////////////////////////////////////

echo "  Detecting taxon ranks...";

//echo "  Extracting third token...";
// Dump third token of name to taxon_rank column
$sql="
ALTER TABLE `$tbl_raw`
ADD COLUMN rank_temp VARCHAR(25) DEFAULT NULL,
ADD INDEX (rank_temp)
;
UPDATE `$tbl_raw`
SET rank_temp=strSplit(`$fld_scientific_name`,' ',3)
;
UPDATE `$tbl_raw`
SET rank_temp=NULL
WHERE TRIM(rank_temp)=''
;
";
sql_execute_multiple($dbh, $sql);
//echo $done;

//echo "  Detecting hybrids...";
// Set rank='hybrid' for any taxon with a hybrid symbol, regardless of rank
$sql="
UPDATE `$tbl_raw`
SET rank_temp='hybrid'
WHERE `$fld_scientific_name` like '% x %' OR `$fld_scientific_name` like 'x %';
";
sql_execute_multiple($dbh, $sql);
//echo $done;

// Get all values of rank_temp. If rank indicator, standardize it
// and transfer to column taxon_rank
//echo "  Updating ranks of infraspecific taxa...";
$results = mysqli_query($dbh, "
SELECT DISTINCT rank_temp FROM `$tbl_raw`
WHERE rank_temp IS NOT NULL;
");

while ($row = mysqli_fetch_assoc($results)) {
	$rank = $row["rank_temp"];
	
	if (isRankIndicator($rank)) {
		$std_rank = stdRankIndicator($rank);
	} elseif ($rank=='hybrid') {
		$std_rank = $rank;
	} else {
		$std_rank = 'species';
	}		
		
	$sql="
	UPDATE `$tbl_raw`
	SET taxon_rank='$std_rank'
	WHERE rank_temp='$rank'
	;		
	";
	sql_execute_multiple($dbh, $sql);

}
//echo $done;

// Mark remaining taxa
$sql="
-- species and hybrids
UPDATE `$tbl_raw`
SET taxon_rank=
CASE
WHEN rank_temp='hybrid' THEN 'hybrid'
ELSE 'species'
END
WHERE taxon_rank IS NULL AND taxon LIKE '% %'
;	
-- families and genera
UPDATE `$tbl_raw`
SET taxon_rank=
CASE
WHEN rank_temp LIKE '%aceae' THEN 'family'
ELSE 'genus'
END
WHERE taxon NOT LIKE '% %'
;	
";	
sql_execute_multiple($dbh, $sql);
//echo $done;

// Remove temporary column
//echo "  Removing temporary column...";
$sql="
ALTER TABLE `$tbl_raw`
DROP COLUMN rank_temp;
";
sql_execute_multiple($dbh, $sql);

echo $done;


?>