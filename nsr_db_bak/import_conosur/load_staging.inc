<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
//
// Omits duplicate records of the same value of taxon 
// + country. Adds status codes from the first of a
// set of multiple country+taxon records. Perhaps run
// manual check to make sure this is not a problem.
///////////////////////////////////////////////////////

echo "Loading raw data to staging table distribution_staging:\r\n";

echo "  Inserting country records for:\r\n";

foreach ( $all_countries as $country ) {
	$country = trim($country);
	
	echo "    $country...";
	$sql="
	INSERT INTO distribution_staging (
	source_name,
	country,
	state_province,
	county_parish,
	taxon,
	taxon_rank,
	native_status,
	cult_status
	)
	SELECT DISTINCT
	'$src',
	'$country',
	NULL,
	NULL,
	taxon,
	taxon_rank,
	status,
	NULL
	FROM `$tbl_raw`
	WHERE $country IS NOT NULL
	;
	";
	sql_execute_multiple($sql);
	echo $done;
	
	if ( ! ($country=='Chile') ) {  // hack to skip Chile

		// Add records for each state
		echo "    Inserting state records...";
		// Loop through each record of raw table
		$sql_all="
		SELECT *
		FROM $tbl_raw
		WHERE $country IS NOT NULL
		;
		";

		$result = mysql_query($sql_all);
		$nrows = mysql_num_rows($result);
		$curr_row = 1;

		while ($row = mysql_fetch_assoc($result)) {	
			echo "\r    Inserting state records...row $curr_row of $nrows        ";
			$taxon = $row["taxon"];
			$taxon_rank = $row["taxon_rank"];
			$status = $row["status"];
			$states = $row[$country];
			$arr_states = explode(",", $states);
	

			foreach ($arr_states as $state) {
				$state = trim($state);
				// Insert the state-level observation
				$sql = "
				INSERT INTO distribution_staging (
				source_name,
				country,
				state_province,
				county_parish,
				taxon,
				taxon_rank,
				native_status
				)
				VALUES ( 
				'$src',
				'$country',
				'$state',
				NULL,
				'$taxon',
				'$taxon_rank',
				'$status'
				)
				;
				";
	
				// add the record
				sql_execute_multiple($sql);					
			}
			$curr_row++;
		}

		$curr_row = $curr_row-1;
		echo "\r    Inserting state records...row $curr_row of $nrows...done\r\n";
	}
}

echo "Fixing state/province spellings...";
$sql="
UPDATE distribution_staging
SET state_province=
CASE
WHEN country='Argentina' AND state_province='BuenosAires' THEN 'Buenos Aires'
WHEN country='Argentina' AND state_province='Catamarca' THEN 'Catamarca'
WHEN country='Argentina' AND state_province='Chaco' THEN 'Chaco'
WHEN country='Argentina' AND state_province='Chubut' THEN 'Chubut'
WHEN country='Argentina' AND state_province LIKE '%rdoba' THEN 'Cordoba'
WHEN country='Argentina' AND state_province='Corrientes' THEN 'Corrientes'
WHEN country='Argentina' AND state_province='DistritoFederal' THEN 'Distrito Federal'
WHEN country='Argentina' AND state_province LIKE 'Entre%' THEN 'Entre Rios'
WHEN country='Argentina' AND state_province='Formosa' THEN 'Formosa'
WHEN country='Argentina' AND state_province='Jujuy' THEN 'Jujuy'
WHEN country='Argentina' AND state_province='LaPampa' THEN 'La Pampa'
WHEN country='Argentina' AND state_province='LaRioja' THEN 'La Rioja'
WHEN country='Argentina' AND state_province='Mendoza' THEN 'Mendoza'
WHEN country='Argentina' AND state_province='Misiones' THEN 'Misiones'
WHEN country='Argentina' AND state_province='Neuquen' THEN 'Neuquen'
WHEN country='Argentina' AND state_province LIKE '%Negro' THEN 'Rio Negro'
WHEN country='Argentina' AND state_province='Salta' THEN 'Salta'
WHEN country='Argentina' AND state_province='SanJuan' THEN 'San Juan'
WHEN country='Argentina' AND state_province='SanLuis' THEN 'San Luis'
WHEN country='Argentina' AND state_province='SantaCruz' THEN 'Santa Cruz'
WHEN country='Argentina' AND state_province='SantaFe' THEN 'Santa Fe'
WHEN country='Argentina' AND state_province='Sgo.delEstero' THEN 'Santiago del Estero'
WHEN country='Argentina' AND state_province LIKE 'Tierra%' THEN 'Tierra del Fuego'
WHEN country='Argentina' AND state_province='Tucu' THEN 'Tucuman'
WHEN country='Argentina' AND state_province LIKE 'Tucum%' THEN 'Tucuman'
WHEN country='Argentina' AND state_province LIKE 'Tucum%' THEN 'Tucuman'
WHEN country='Argentina' AND state_province LIKE 'Tucum%' THEN 'Tucuman'
WHEN country='Brazil' AND state_province='Parana' THEN 'Parana'
WHEN country='Brazil' AND state_province='RioGrandeDoSul' THEN 'Rio Grande do Sul'
WHEN country='Brazil' AND state_province='SantaCatarina' THEN 'Santa Catarina'
WHEN country='Paraguay' AND state_province LIKE '%eembuc%' THEN 'Neembucu'
WHEN country='Paraguay' AND state_province='AltoParaguay' THEN 'Alto Paraguay'
WHEN country='Paraguay' AND state_province LIKE 'Alto%' AND state_province<>'AltoParaguay' THEN 'Alto Parana'
WHEN country='Paraguay' AND state_province='Amambay' THEN 'Amambay'
WHEN country='Paraguay' AND state_province LIKE 'Caaguaz%' THEN 'Caaguazu'
WHEN country='Paraguay' AND state_province LIKE 'Caazap%' THEN 'Caazapa'
WHEN country='Paraguay' AND state_province LIKE 'Canindey%' THEN 'Canindeyu'
WHEN country='Paraguay' AND state_province='Central' THEN 'Central'
WHEN country='Paraguay' AND state_province LIKE 'Concepci%n' THEN 'Concepcion'
WHEN country='Paraguay' AND state_province='Cordillera' THEN 'Cordillera'
WHEN country='Paraguay' AND state_province LIKE 'Guair%' THEN 'Guaira'
WHEN country='Paraguay' AND state_province LIKE 'Itap%a' THEN 'Itapua'
WHEN country='Paraguay' AND state_province='Misiones' THEN 'Misiones'
WHEN country='Paraguay' AND state_province LIKE 'Paraguar%' THEN 'Paraguari'
WHEN country='Paraguay' AND state_province='PresidenteHayes' THEN 'Presidente Hayes'
WHEN country='Paraguay' AND state_province='SanPedro' THEN 'San Pedro'
WHEN country='Uruguay' AND state_province='Artigas' THEN 'Artigas'
WHEN country='Uruguay' AND state_province='Canelones' THEN 'Canelones'
WHEN country='Uruguay' AND state_province='CerroLargo' THEN 'Cerro Largo'
WHEN country='Uruguay' AND state_province='Colonia' THEN 'Colonia'
WHEN country='Uruguay' AND state_province='Durazno' THEN 'Durazno'
WHEN country='Uruguay' AND state_province='Flores' THEN 'Flores'
WHEN country='Uruguay' AND state_province='Florida' THEN 'Florida'
WHEN country='Uruguay' AND state_province='Lavalleja' THEN 'Lavalleja'
WHEN country='Uruguay' AND state_province='Maldonado' THEN 'Maldonado'
WHEN country='Uruguay' AND state_province='Montevideo' THEN 'Montevideo'
WHEN country='Uruguay' AND state_province LIKE 'Paysand%' THEN 'Paysandu'
WHEN country='Uruguay' AND state_province LIKE '%Negro' THEN 'Rio Negro'
WHEN country='Uruguay' AND state_province='Rivera' THEN 'Rivera'
WHEN country='Uruguay' AND state_province='Rocha' THEN 'Rocha'
WHEN country='Uruguay' AND state_province='Salto' THEN 'Salto'
WHEN country='Uruguay' AND state_province LIKE 'San%' THEN 'San Jose'
WHEN country='Uruguay' AND state_province='Soriano' THEN 'Soriano'
WHEN country='Uruguay' AND state_province LIKE '%Orientales%' THEN 'Treinta y Tres'
WHEN country='Uruguay' AND state_province LIKE 'Tacuaremb%' THEN 'Tacuarembo'
ELSE state_province
END
;
";
sql_execute_multiple($sql);
echo $done;

echo "Standardizing native_status...";
$sql="
UPDATE distribution_staging
SET native_status=
CASE
WHEN trim(native_status)='' THEN NULL
WHEN native_status='Adventicia' THEN 'Introduced'
WHEN native_status='Cosmopolita' THEN 'Native'
WHEN native_status LIKE 'End%' THEN 'Endemic'
WHEN native_status='Introducida' THEN 'Introduced'
WHEN native_status='Nativa' THEN 'Native'
WHEN native_status='Naturalizada' THEN 'Introduced'
ELSE NULL
END
;
";
sql_execute_multiple($sql);
echo $done;


?>