NSR (Native Status Resolver)

Created by: Brad Boyle
Email: bboyle AT email dot arizona dot edu OR ojalaquellueva AT gmail dot com
Date created: 2 April 2014
Last revision date: 2 April 2014

Purpose: 

Determines if a plant observed at a particular location is (a) native or non-native, 
and (b) cultivated or naturally occurring.

Description:

An "observation" is a record of a taxon accompanied by the political division in which it 
was observed. Up to three political divisions can be used (country, stateProvince, countyParish). 
The algorithm checks the observation against checklists for one or more of the three political 
divisions. Checklists can be comprehensive (i.e., they include all known species within the 
political division) or partial (only some species included, for example, lists of endemic or 
introduced species). For each observation, the basis of the decision and the lists consulted 
to make that decision are reported. Observations for which no checklists are available for 
any of the political division are flagged as "No information".

The main scripts are as follows. Only main scrips end in ".php"; these scripts call all others.

1. nsr_db.php
- Builds the NSR reference database by importing & standardizing different sources. Each source 
must be placed in a directory whose name begins with "import_", the remainder of the directory 
name is a short, unique (3-10 characters) abbreviation for that source. Scripts performing 
source-specific standardizations are placed within this folder. See some of the existing 
import directories for examples of how these standardizations are performed. 
- After import, all remaining standardizations are generic.

2. test_nsr.php
- Validates the NSR reference database, reporting errors, if any.

3. load_observations.php
- Imports CSV file of raw species observations to table `observation` in the NSR database. 

4. nsr.php
- NSR batch processing application.
- Evaluates native and cultivated status of species observations against reference database of 
annotated distribution checklists.
- Requires existing reference database, built with create_nsr.php and validated with test_nsr.php.
- Assumes raw observations have been previously uploaded to NSR database, using script 
load_observations.php.

Notes:
1. Set parameters in global_params.inc and any local params.inc files within 
subdirectories.
