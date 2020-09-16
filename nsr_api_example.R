###############################################
# Example use of NSR Batch API
# By: Brad Boyle (bboyle@email.arizona.edu)
# Date: 6 Feb. 2019
# Last updated: 15 Sep. 2020
# Compatible with NSR version: 2.3+
###############################################

# Base url for NSR Batch API
url = "https://bien.nceas.ucsb.edu/nsr/nsr_wsb.php"		# Production (server name)
url = "https://nsrapi.xyz/nsr_wsb.php"								# Production (domain name)

# Load libraries
library(RCurl)		# API requests
# library(rjson)		# JSON coding/decoding
library(jsonlite) # JSON coding/decoding

# Read in example file of taxon observations
# See the BIEN website for details on how to organize an 
# NSR input file a:
# http://bien.nceas.ucsb.edu/bien/tools/nsr/batch-mode/
example_file <- "nsr_testfile.csv"
obs <- read.csv( example_file, header=TRUE)

# Inspect the input
obs

# Convert to JSON
#data_json <- toJSON(unname(split(obs, 1:nrow(obs))))
data_json <- toJSON(unname(obs))

#################################
# Example 1: Resolve mode
#################################

# Set the NSR processing option
mode <- "resolve"		# Resolve native status of taxon observation

# Convert the options to data frame and then JSON
opts <- data.frame( c(mode) )
names(opts) <- c("mode")
opts_json <-  jsonlite::toJSON(opts)
opts_json <- gsub('\\[','',opts_json)
opts_json <- gsub('\\]','',opts_json)

# Combine the options and data into single JSON object
input_json <- paste0('{"opts":', opts_json, ',"data":', data_json, '}' )

# Construct the request
headers <- list('Accept' = 'application/json', 'Content-Type' = 'application/json', 'charset' = 'UTF-8')

# Send the API request
results_json <- postForm(url, .opts=list(postfields= input_json, httpheader=headers))

# Convert the JSON results to data frame
results <- as.data.frame( fromJSON(results_json) )

# Tidy up
results <- t(results)						# Transpose
colnames(results) = results[1,] 		# Get header names from first row
results = results[-1, ]          			# Remove the first row.
results <- as.data.frame(results)	# Convert to dataframe (again)
rownames(results) <- NULL			# Reset row numbers

# Inspect the results
head(results, 10)

# That's a lot of columns. Let's display one row vertically
# to get a better understanding of the output fields
results.t <- t(results[,2:ncol(results)]) 
results.t <- results.t[,1,drop =FALSE]
noquote(results.t)

# Display the main results columns for all rows
results[ , c("family", "genus", "species", "country", "state_province", "county_parish", "native_status", "isIntroduced", "native_status_sources", "native_status_reason")]




#################################
# Example 2: Get metadata for current NSR version
#################################
rm( list = Filter( exists, c("input_json") ) )
rm( list = Filter( exists, c("results_json") ) )
rm( list = Filter( exists, c("results") ) )

# All we need to do is reset option mode.
# all other options will be ignored
mode <- "meta"		

# Reform the options json again
opts <- data.frame(c(mode))
names(opts) <- c("mode")
opts_json <- jsonlite::toJSON(opts)
opts_json <- gsub('\\[','',opts_json)
opts_json <- gsub('\\]','',opts_json)

# Make the options + data JSON
input_json <- paste0('{"opts":', opts_json, ',"data":', data_json, '}' )

# Send the request again
results_json <- postForm(url, .opts=list(postfields= input_json, httpheader=headers))

results <-fromJSON(results_json)
print( results )

#################################
# Example 3: Get metadata for all NSR sources
#################################
rm( list = Filter( exists, c("input_json") ) )
rm( list = Filter( exists, c("results_json") ) )
rm( list = Filter( exists, c("results") ) )

# Set sources mode
mode <- "sources"		

# Reform the options json again
opts <- data.frame(c(mode))
names(opts) <- c("mode")
opts_json <- jsonlite::toJSON(opts)
opts_json <- gsub('\\[','',opts_json)
opts_json <- gsub('\\]','',opts_json)

# Make the options + data JSON
input_json <- paste0('{"opts":', opts_json, ',"data":', data_json, '}' )

# Send the request again
results_json <- postForm(url, .opts=list(postfields= input_json, httpheader=headers))

results <-fromJSON(results_json)
print( results )

#################################
# Example 4: Get bibtex citations for all 
# checklist sources and the NSR itself
#################################
rm( list = Filter( exists, c("input_json") ) )
rm( list = Filter( exists, c("results_json") ) )
rm( list = Filter( exists, c("results") ) )

# Set citations mode
mode <- "citations"		

# Reform the options json again
opts <- data.frame(c(mode))
names(opts) <- c("mode")
opts_json <- jsonlite::toJSON(opts)
opts_json <- gsub('\\[','',opts_json)
opts_json <- gsub('\\]','',opts_json)

# Make the options + data JSON
input_json <- paste0('{"opts":', opts_json, ',"data":', data_json, '}' )

# Send the request again
results_json <- postForm(url, .opts=list(postfields= input_json, httpheader=headers))

results <-jsonlite::fromJSON(results_json)
print( results )
