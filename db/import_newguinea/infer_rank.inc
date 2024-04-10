<?php

//////////////////////////////////////////////////////////////////
// Detect rank of taxon
//////////////////////////////////////////////////////////////////

echo "  Detecting taxon ranks...";

//echo "  Extracting third token...";
// Dump third token of name to taxon_rank column
$sql="
ALTER TABLE $tbl_raw_final
ADD COLUMN rank_temp VARCHAR(25) DEFAULT NULL,
ADD INDEX (rank_temp);
UPDATE $tbl_raw_final
SET rank_temp=strSplit(taxon,' ',3)
";
sql_execute_multiple($dbh, $sql);
//echo $done;

//echo "  Detecting hybrids...";
// Dump third token of name to taxon_rank column
$sql="
UPDATE $tbl_raw_final
SET rank_temp='hybrid'
WHERE taxon like '% x %' OR taxon like 'x %';
";
sql_execute_multiple($dbh, $sql);
//echo $done;

// Get all values of rank_temp. If rank indicator, standardize it
// and transfer to column taxon_rank
//echo "  Updating ranks of infraspecific taxa...";
$results = mysqli_query($dbh, "
SELECT DISTINCT rank_temp FROM $tbl_raw_final;
");

while ($row = mysqli_fetch_assoc($results)) {
	$rank = $row["rank_temp"];
	
	if (isRankIndicator($rank)) {
		$std_rank = stdRankIndicator($rank);
		$sql="
		UPDATE $tbl_raw_final
		SET taxon_rank='$std_rank'
		WHERE rank_temp='$rank'
		;		
		";
		sql_execute_multiple($dbh, $sql);
	}
}
//echo $done;

// Mark remaining rows as species
//echo "  Marking species and hybrids...";
$sql="
UPDATE $tbl_raw_final
SET taxon_rank=
CASE
WHEN rank_temp='hybrid' THEN 'hybrid'
ELSE 'species'
END
WHERE taxon_rank IS NULL
;		
";	
sql_execute_multiple($dbh, $sql);
//echo $done;

// Remove temporary column
//echo "  Removing temporary column...";
$sql="
ALTER TABLE $tbl_raw_final
DROP COLUMN rank_temp;
";
sql_execute_multiple($dbh, $sql);

echo $done;

?>