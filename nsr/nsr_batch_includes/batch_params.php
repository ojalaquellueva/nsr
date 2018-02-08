<?php

$JOB_WHERE = " o.job='$job' ";
$JOB_WHERE_NA = " job='$job' ";

// Names of input file for batch processing
// This can be over-ridden by supplying -f parameter in command line
$inputfilename = "nsr_input.csv";

// MySQL LOAD DATA INFILE command batch default options
// Assumes CSV file with header and Mac line endings
$local = " LOCAL ";	// LOCAL keyword
$fields_terminated_by = " FIELDS TERMINATED BY ',' ";
$optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  
$lines_terminated_by = " LINES TERMINATED BY '\r' "; 	// Legacy Mac
$ignore_lines = " IGNORE 1 LINES ";	// Ignore header line

?>