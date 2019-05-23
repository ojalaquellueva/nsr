# NSR (Native Status Resolver) Database


### Overview

Builds the NSR reference database by importing & standardizing different sources. Each source must be placed in a directory whose name begins with "import_", the remainder of the directory name is a short, unique (3-10 characters) abbreviation for that source. Scripts performing source-specific standardizations are placed within this folder. See existing import directories for examples of how these standardizations are performed. After import, all remaining standardizations are generic.

### Preparation

Set parameters in global_params.inc and any local params.inc files within 
subdirectories.

### Usage

```
php nsr_db.php
```

### Permissions

You should have at least four users for this database: 

1. An admin-level superuser (assume admin)
2. A write/execute/create level user (assume nsr)
3. Another write/execute/create level user (assume nsr_write)
4. A read-only user (assume nsr_read)

 In addition, you might want a fifth read-only user just for the api:

5. A read-only user for the api (assume nsr_api)

Assuming the first three users above, you will need to set permissions for database "nsr" as follows, logged into MySQL as root. Assumes the users have already been created. Note that this will only work for local connections. For remote connections you need to execute all the same grants again, using 'user'@'%' instead of 'user'@'localhost'.

```
--
-- Revoke all privileges to start
--
REVOKE ALL PRIVILEGES ON nsr.* FROM nsr_read@localhost;
REVOKE ALL PRIVILEGES ON nsr.* FROM nsr_write@localhost;
REVOKE ALL PRIVILEGES ON nsr.* FROM nsr@localhost;
REVOKE ALL PRIVILEGES ON nsr.* FROM admin@localhost;


--
-- nsr_read (select only)
--
GRANT SELECT ON nsr.* TO 'nsr_read'@'localhost';

--
-- nsr_write (needs write/execute)
-- 
GRANT SELECT, INSERT, UPDATE, DELETE 
ON nsr.* TO 'nsr_write'@'localhost';
GRANT DROP ON TABLE nsr.* TO 'nsr_write'@'localhost';
GRANT CREATE ON TABLE nsr.* TO 'nsr_write'@'localhost';
GRANT EXECUTE ON nsr_write.* TO 'nsr'@'localhost';

--
-- nsr (needs write/execute)
-- 
GRANT SELECT, INSERT, UPDATE, DELETE, ALTER 
ON nsr.* TO 'nsr'@'localhost';
GRANT DROP ON TABLE nsr.* TO 'nsr'@'localhost';
GRANT CREATE ON TABLE nsr.* TO 'nsr'@'localhost';
GRANT EXECUTE ON nsr.* TO 'nsr'@'localhost';

--
-- admin (needs all permissions)
-- 
GRANT ALL ON nsr.* TO 'admin'@'localhost';

FLUSH PRIVILEGES;