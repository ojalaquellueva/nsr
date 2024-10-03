<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

echo "Loading raw data:\r\n";

# Just sample the distribution file if applicable
$file_raw=$file_dist_raw;
$data_raw="$datapath$file_raw";
if ( ! $ROW_LIMIT=="" ) {
	$data_raw_sample = $datapath . "raw_data_sample";
	$cmd="head -{$ROW_LIMIT} $datapath$file_raw > $data_raw_sample";	
	//echo "Running command: '" . $cmd . "'\n";
	exec($cmd, $output, $status);
	if ($status) die("ERROR: command \'{$cmd}\' failed (" . basename(__FILE__) . ")\n");	
	$data_raw=$data_raw_sample;
}

// Distribution file
$file_raw=$file_dist_raw;
echo "  '$file_raw' --> `$tbl_dist_raw`...";
$sql = "
LOAD DATA $local INFILE '$data_raw' 
INTO TABLE $tbl_dist_raw
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Setting empty strings to NULL...";
if (!(empty_string_to_null($dbh, $tbl_dist_raw))) die("Error\r\n.");
echo $done;
echo "    Setting NA to NULL...";
if (!(NA_to_null($dbh, $tbl_dist_raw))) die("Error\r\n.");
echo $done;

// Names file
$file_raw=$file_names_raw;
echo "  '$file_raw' --> `$tbl_names_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw' 
INTO TABLE $tbl_names_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Setting empty strings to NULL...";
if (!(empty_string_to_null($dbh, $tbl_names_raw))) die("Error\r\n.");
echo $done;
echo "    Setting NA to NULL...";
if (!(NA_to_null($dbh, $tbl_names_raw))) die("Error\r\n.");
echo $done;


echo "  `$tbl_region_codes`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_codes' 
INTO TABLE $tbl_region_codes 
FIELDS TERMINATED BY ',' 
OPTIONALLY ENCLOSED BY '\"'
LINES TERMINATED BY '\r\n' 
IGNORE 1 LINES
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Setting empty strings to NULL...";
if (!(empty_string_to_null($dbh,$tbl_region_codes))) die("Error\r\n.");
echo $done;
echo "    Setting NA to NULL...";
if (!(NA_to_null($dbh, $tbl_region_codes))) die("Error\r\n.");
echo $done;

?>
