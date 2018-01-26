Setting NSR access to db configuration files

Application directory (on nimoy):
/var/www/bien/apps/nsr/

Configuration file directory:
/var/www/config/bien/apps/nsr/

Config files (go in above directory):
db_config.php
db_configw.php

Set ownership, group and permissions for config directories and files:
$ cd /var/www/
$ sudo chown -R www-data config
$ sudo chgrp -R bien config
$ sudo chmod -R 570 config
$ sudo chmod g+s config

