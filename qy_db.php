<?php

////////////////////////////////////////////////////////
// Queries database with supplied sql ($sql)
////////////////////////////////////////////////////////


/*
// For testing only
$CONFIG_DIR="/home/boyle/bien/nsr/config/";
include 'params.php';
$mode="citations";
$sql="
SELECT s.source_id, s.source_name, s.source_name_full as checklist_details, 
s.date_accessed, s.citation AS source_citation,
group_concat(ps.poldiv_name) AS countries
FROM poldiv_source ps JOIN `source` s ON ps.source_id=s.source_id 
WHERE ps.poldiv_type='country' 
GROUP BY s.source_id
ORDER BY s.source_id, s.source_name
;
";
*/

include $CONFIG_DIR.'db_config.php';

// On error, display SQL if request (turn off for production!)
if ( $err_show_sql ) {
	$sql_disp = " SQL: " . $sql;
} else {
	$sql_disp = "";
}

// connect to the db
$link = mysqli_connect($HOST,$USER,$PWD,$DB);

// check connection
if (mysqli_connect_errno()) {
	echo "Connection failed: ". mysqli_connect_error();
	exit();
}

$qy = mysqli_query($link,$sql) or die('Query failed!'.$sql_disp);

// create one master array of the records
$results_array = array();
if(mysqli_num_rows($qy)) {
	while($result = mysqli_fetch_assoc($qy)) {
		$results_array[] = array($mode=>$result);
	}
}

/* disconnect from the db */
@mysqli_close($link);

?>