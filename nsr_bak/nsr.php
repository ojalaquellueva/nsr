<?php

///////////////////////////////////////////////
// Evaluates observations against nsr
// database and adds results to cache
// Connection to db must already exist
///////////////////////////////////////////////

include "dbw_open.php";

//include $nsr_includes_dir."check_absence.php";
include $nsr_includes_dir."check_presence.php";
include $nsr_includes_dir."check_cultivated.php";
include $nsr_includes_dir."infer_status.php";
include $nsr_includes_dir."append_to_cache.php";

include "db_close.php";

?>