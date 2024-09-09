# Hotfixes

## Overview

This directory contains "hotfixes" only: scripts that apply bugfixes or add information or enhancements to an existing application, without rebuilding the entire database or issuing a full major application release. A single hotfix is a script or set of scripts that are executed together, manually, on a live application, after which the database, code and overall application version numbers are incremented (see **Versioning** for details). The latter step is always executed by a script named `update_metadata.sql`, which inserts a new record to database table "meta" and increments version numbers. All scripts pertaining to a particular hotfix are grouped in a single hotfix directory named for incremented application version number applied after the hotfix was completed.

Hotfixes involving the database are not part of the code pipeline that built or refreshed the current production database. Ideally, however, all past hotfixes are integrated into the pipeline code associated within the next major release, as indicated by an increment in the `[major_version]` coomponent of the one or more the three BIEN application version numbers (see **Versioning**).

## Versioning

### Version number system

BIEN applicationsd use semantic versioning, with three-part version numbers consisting of three integers separated by a period. The three parts, from left to right, are: `[major_version].[minor_version].[patch]`.  

### Hotfix version number changes

Version number updates associated with hotfixes involve incrementing either the minor or patch component of the three-part version number, depending on the impact of the changes. Changes associated with an increment to the minor version may required changes in depended applications, code or data (e.g., scripts used to call a BIEN API). Patches fix known issues but generally do not require dependent code changes and in most cases will go unnoticed by users.

### Version number types

Three types of version numbers are associated with most BIEN applications:

1. **Code version**
  * This is identical to the Git tag number assigned when code changes warrant a version number increment. If changes in database content do not involve application code changes (for example, refreshing reference data with existing code) then the code version number will remain unchanged.
2. **Database version**
  * The reference database has its own version number, assigned whenever database structure or content changes. If application code changes do not result in changes to the database, then the database version remains unchanged.
3. **Application version**
  * An overall version number that increases whenever *either* the code version or the database version change. This is the version number that is displayed in the header of the landing page of BIEN API web interfaces.

## Hotfix archive

Typically, the changes implemented by previous hotfixes are integrated into the main appliation code and database pipeline code of the next major release. After integration, the hotfixes are moved to the subdirectory `archive/` and grouped together in a folder named for the major version into which they were integrated.
