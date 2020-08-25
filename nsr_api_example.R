###############################################
# Example use of NSR API
# By: Brad Boyle (bboyle@email.arizona.edu)
# Date: 6 Feb. 2019
# Updated: 25 Aug. 2020
###############################################

# Base url for NSR Batch API
url = "https://bien.nceas.ucsb.edu/nsr/nsr_wsb.php"		# Production (server name)
url = "https://nsrapi.xyz/nsr_wsb.php"		# Production (domain name)

# Load libraries
library(RCurl)		# API requests
library(rjson)		# JSON coding/decoding

# Read in example file of taxon observations
# See the BIEN website for details on how to organize an NSR input file, see:
# http://bien.nceas.ucsb.edu/bien/tools/nsr/batch-mode/
example_file <- "nsr_testfile.csv"
obs <- read.csv( example_file, header=TRUE)

# Inspect the input
obs

# Convert to JSON
obs_json <- toJSON(unname(split(obs, 1:nrow(obs))))

# Construct the request
headers <- list('Accept' = 'application/json', 'Content-Type' = 'application/json', 'charset' = 'UTF-8')
results_json <- postForm(url, .opts=list(postfields=obs_json, httpheader=headers))

# Give the input file name to the function.
results <- fromJSON(results_json)

# Convert JSON file to a data frame
# This takes a bit of work
results <- as.data.frame(results)	# Convert to dataframe
results <- t(results)						# Transpose
colnames(results) = results[1,] 	# Get header names from first row
results = results[-1, ]          			# Remove the first row.
results <- as.data.frame(results)	# Convert to dataframe (again)
rownames(results) <- NULL			# Reset row numbers

# Inspect the results
head(results, 10)

# That's a lot of columns. Let's display one row vertically
# to get a better understanding of the output fields
results.t <- t(results[,2:ncol(results)]) 
results.t[,1,drop =FALSE]

# Display the main results columns for all rows
results[ , c("family", "genus", "species", "country", "state_province", "native_status", "isIntroduced", "native_status_sources", "native_status_reason")]
