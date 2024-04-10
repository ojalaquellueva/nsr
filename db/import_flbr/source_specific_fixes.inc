<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////


echo "  Populating state_province...";
$sql="
UPDATE `$tbl_raw` 
SET state_province=
CASE
WHEN state_code='BR-AC' THEN 'Acre'
WHEN state_code='BR-AL' THEN 'Alagoas'
WHEN state_code='BR-AM' THEN 'Amazonas'
WHEN state_code='BR-AP' THEN 'Amapa'
WHEN state_code='BR-BA' THEN 'Bahia'
WHEN state_code='BR-CE' THEN 'Ceara'
WHEN state_code='BR-DF' THEN 'Distrito Federal'
WHEN state_code='BR-ES' THEN 'Espirito Santo'
WHEN state_code='BR-GO' THEN 'Goias'
WHEN state_code='BR-MA' THEN 'Maranhao'
WHEN state_code='BR-MG' THEN 'Minas Gerais'
WHEN state_code='BR-MS' THEN 'Mato Grosso do Sul'
WHEN state_code='BR-MT' THEN 'Mato Grosso'
WHEN state_code='BR-PA' THEN 'Para'
WHEN state_code='BR-PB' THEN 'Paraiba'
WHEN state_code='BR-PE' THEN 'Pernambuco'
WHEN state_code='BR-PI' THEN 'Piaui'
WHEN state_code='BR-PR' THEN 'Parana'
WHEN state_code='BR-RJ' THEN 'Rio de Janeiro'
WHEN state_code='BR-RN' THEN 'Rio Grande do Norte'
WHEN state_code='BR-RO' THEN 'Rondonia'
WHEN state_code='BR-RR' THEN 'Roraima'
WHEN state_code='BR-RS' THEN 'Rio Grande do Sul'
WHEN state_code='BR-SC' THEN 'Santa Catarina'
WHEN state_code='BR-SE' THEN 'Sergipe'
WHEN state_code='BR-SP' THEN 'Sao Paulo'
WHEN state_code='BR-TO' THEN 'Tocantins'
ELSE NULL
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;


?>