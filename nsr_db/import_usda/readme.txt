The scripts in this folder add a download of USDA Plants to the cultivated species database.

For now, the download must be obtained manually using the Advanced Search utility at https://plants.usda.gov/adv_search.html. Select to Display following fields:

State and Province
Scientific Name (displayed by default; leave default "Display rank" options checked)
Genus
Family
Native Status

Do not set any additional display options or filter criteria. Check the option "Download text file without formatted display" and press the button "Display Results". The results will be dumped as comma-delimited text to your browser. It should have the following headings:

"Accepted Symbol",
"Synonym Symbol",
"Scientific Name",
"State and Province",
"Genus",
"Family",
"Native Status"

Copy all and paste to a plain text file. Use a plain text application such as TextWrangler; do NOT use Excel or MS Word. Place this file in the data/ directory of the import_usda directory. In params.inc set the value of $file_raw equal to the name of this file.




