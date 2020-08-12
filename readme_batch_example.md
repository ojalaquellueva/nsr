# Example command for testing nsr_batch

* Uses example names file "testfile.csv" in example data directory (data/user/)

``` 
php nsr_batch.php -e=true -i=true -f="testfile.csv" -l=unix -t=csv -r=true
```

#### Options  
* Default values in **bold** 

| Option	| Meaning | Values
| --------- | ------------------- | --------------------
| -e | terminal echo on | __true__,false
| -i | interactive mode | true,__false__ 
| -f | input file name |  
| -l | line-endings | unix,__mac__,win
| -t | inputfile type | __csv__,tab
| -r | replace the cache | true,__false__  
