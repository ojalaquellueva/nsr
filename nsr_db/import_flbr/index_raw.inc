<?php

////////////////////////////////////////////////
// Index the "raw-raw" data tables after loading
////////////////////////////////////////////////

// table raw will be indexed later after loading
echo "Indexing raw data tables:\r\n";

echo "  $tbl_dist_raw...";
$sql="
ALTER TABLE $tbl_dist_raw
ADD INDEX (id),
ADD INDEX (countryCode),
ADD INDEX (establishmentMeans)
; 
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  $tbl_taxon_raw...";
$sql="
ALTER TABLE $tbl_taxon_raw
ADD INDEX (id),
ADD INDEX (taxonID),
ADD INDEX (acceptedNameUsageID),
ADD INDEX (parentNameUsageID),
ADD INDEX (originalNameUsageID),
ADD INDEX (scientificName),
ADD INDEX (parentNameUsage),
ADD INDEX (higherClassification),
ADD INDEX (phylum),
ADD INDEX (`class`),
ADD INDEX (`order`),
ADD INDEX (family),
ADD INDEX (genus),
ADD INDEX (specificEpithet),
ADD INDEX (infraspecificEpithet),
ADD INDEX (taxonRank),
ADD INDEX (taxonomicStatus),
ADD INDEX (nomenclaturalStatus)
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>