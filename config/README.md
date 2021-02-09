# Server-specific database and configuration parameters

* Set all parameters in all files in this directory
* Move entire config directory to base directory
* Base directory is the parent directory of application directory `src/`
* Make sure the first include line in src/params.php points is as follows:

```
include "../config/server_config.php";
```

This will enable all other parameters to be set