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
