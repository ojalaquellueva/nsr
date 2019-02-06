# Example command for testing nsr_batch

* Uses example names file "testfile.csv" in example data directory (data/user/)
* Assumes parameter $DATADIR="user/data" (see params.php)

``` 
php nsr_batch.php -e=true -i=true -f="testfile.csv" -l=unix -t=csv -r=false
```
