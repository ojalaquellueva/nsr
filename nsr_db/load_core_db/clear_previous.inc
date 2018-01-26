<?php

///////////////////////////////////////////////////////////////////
// Removes from core db all records related only to this source
///////////////////////////////////////////////////////////////////

echo "  Removing previous distribution records linked only to this source...";
$sql="
DELETE d.*
FROM distribution d JOIN source s
ON d.source_id=s.source_id
WHERE s.source_name='$source_name';
";
sql_execute_multiple($sql);
echo $done;

echo "  Removing cultivated species records linked only to this source...";
$sql="
DELETE c.*
FROM cultspp c JOIN source s
ON c.source_id=s.source_id
WHERE s.source_name='$source_name';
";
sql_execute_multiple($sql);
echo $done;


?>
