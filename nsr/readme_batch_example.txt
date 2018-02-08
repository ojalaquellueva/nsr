# Test:
php nsr_batch.php -e=true -i=true -f="testfile.csv" -l=unix -t=csv -r=false

# Bigger test:
php nsr_batch.php -e=true -i=true -f="nsr_submitted_dev2.csv" -l=unix -t=csv -r=false

# The real deal:
php nsr_batch.php -e=true -i=true -f="nsr_submitted.complete.csv" -l=unix -t=csv -r=false