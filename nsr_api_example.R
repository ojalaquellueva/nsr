###############################################
# R NSR API Example
###############################################

rm(list=ls())

#################################
# Parameters & libraries
#################################

##################
# Base URL
##################

url = "https://bien.nceas.ucsb.edu/nsr/nsr_wsb.php"

##################
# Libraries
##################

library(httr)		# API requests
library(jsonlite) # JSON coding/decoding

##################
# Test data
##################

# Test data
# For details on how to organize an NSR input file, see:
# http://bien.nceas.ucsb.edu/bien/tools/nsr/batch-mode/
example_file <- "https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2023/06/nsr_testfile.csv"

# Set TRUE to use sample of 10 rows of data, FALSE to use all
data.use.sample <- FALSE

##################
# Misc parameters
##################

# API variables to clear before each API call
# Avoids spillover between calls
api_vars <- c("mode")

# Response variables to clear before each API call
# Avoids confusion with previous results if API call fails
response_vars <- c("request_json", "response_json", "response")

#################################
# Functions
#################################

make_request_json <- function( 
	mode,				# API mode; required
	data=NULL 	# Raw data; required if mode=='resolve'
	) {
	######################################
	# Accepts: options parameters and (optionally) data
	# Returns: formatted JSON api request
	######################################
	
	# Set defaults if applicable
	if ( mode=="resolve"  )  {
		# Convert raw data to JSON
		if (is.null(data) ) stop("ERROR: mode 'resolve' requires data!\n")
		data_json <- jsonlite::toJSON(unname(data))
	} 
	
	opts <- data.frame(mode = mode)
	opts_json <-  jsonlite::toJSON(opts)
	opts_json <- gsub('\\[','',opts_json)
	opts_json <- gsub('\\]','',opts_json)
	
	# Combine the options and data into single JSON object
	if ( mode=="resolve" ) {
		input_json <- paste0('{"opts":', opts_json, ',"data":', data_json, '}' )
	} else {
		input_json <- paste0('{"opts":', opts_json, '}' )
	}
	
	return(input_json)
}

send_request_json <- function( url, request_json ) {
	###################################
	# Accepts: API url + JSON options & data
	# Sends: POST request to url, with JSON
	#		attached to body
	# Returns: JSON response
	###################################
	if ( is.null(url) || is.na(url) ) {
		stop("ERROR: parameter 'url' missing (function send_request_json()'\n")
	}
	if ( is.null(request_json) || is.na(request_json) ) {
		stop("ERROR: parameter 'json_body' missing (function send_request_json()'\n")
	}
	
	response_json <- POST(url = url,
	                  add_headers('Content-Type' = 'application/json'),
	                  add_headers('Accept' = 'application/json'),
	                  add_headers('charset' = 'UTF-8'),
	                  body = request_json,
	                  encode = "json"
	                  )

	return(response_json)
}

decode_response_json <- function( response_json, mode ) {
	###################################
	# Converts resonse json to data frame
	# Also decodes weird format of NSR JSON
	###################################
	
	response_raw <- fromJSON( rawToChar( response_json$content ) ) 
	response <- as.data.frame(response_raw)
	
	if ( mode=="resolve") {
		# Extra transformations needed due to weird NSR response data format
		col.names <- response$id
		response <- as.data.frame(t(response[,-1]))
		colnames(response) <- col.names
		
		# Convert f'ing factors to character
		factor_columns <- sapply(response, is.factor)
		response[factor_columns] <- lapply(
			response[factor_columns], as.character
			)
		# Convert numeric columns
		response$isIntroduced <- as.integer(response$isIntroduced)
		response$isCultivatedNSR <- as.integer(response$isCultivatedNSR)
		
		# Reset row numbers
		row.names(response) <- 1:nrow(response)
	} else {
		# Unnest
		response <- response[[1]]
	}
	
	return( response )
}

get_request <- function(
		url, 					# Required
		mode,				# Required
		data=NULL 	# Raw data; required if mode=='resolve)
	) {
	######################################
	# Accepts: options parameters and (optionally) data
	#		required for API request
	# Sends: POST request to API
	# Returns: response formatted as data frame
	# 
	# Meta-function which combine functions 
	# make_request_json, send_request_json & 
	# decode_response_json. See component 
	# functions for details
	######################################
	if ( is.null(url) || is.na(url) ) {
		stop("ERROR: parameter 'url' missing (function get_request()'\n")
	}
	if ( is.null(mode) || is.na(mode) ) {
		stop("ERROR: parameter 'mode' missing (function get_request()'\n")
	}

	request_json <- make_request_json(
		mode=mode,
		data= data 
		)
	response_json <- send_request_json( url, request_json )
	response_df <- decode_response_json( response_json, mode=mode )
	
	# if ( ncol(response_df)==1 ) {
		# colnames(response_df) <- "error"
		# response_df$http_status <- response_json$status
	# }

	return( response_df )
}

specify_decimal <- function(x, k) {
	# Set fixed number of decimals
	if ( is.na(x) || is.null(x) ) {
		x.formatted <- x
	} else {
		x.formatted <- format(round(x, k), nsmall=k)
	}
	return( x.formatted )
}

#################################
# Selected metadata checks
#
# Available metadata calls: 
# "meta", "sources", "citations", "checklist_countries", "country_checklists"
# print(response) to see the complete results of each call
#################################

# Application version and database version
mode <- "meta"		
rm( list = Filter( exists, response_vars ) )
# request_json <- make_request_json(mode=mode)
# response_json <- send_request_json( url, request_json )
# response <- decode_response_json(response_json)
response <- get_request(url=url, mode=mode)
db_version  <- response$db_version
db_date   <- response$build_date
if( "app_version" %in% colnames(response) ) {
	app_version  <- response$app_version
} else {
	app_version  <- response$code_version
}

# Available sources
mode <- "sources"		
rm( list = Filter( exists, response_vars ) )
response <- get_request(url=url, mode=mode)
source.details <- response

# App and source citations
mode <- "citations"		
rm( list = Filter( exists, response_vars ) )
citations <- get_request(url=url, mode=mode)

# Display results
cat("NSR version: ", app_version, "\n")
cat("DB version: ", db_version, " (", db_date, ")\n")
cat("Checklists:\n")
print(source.details, row.names=FALSE)
cat("Citations:")
print(citations, row.names=FALSE)

#################################
# Load test data
#################################

data <- read.csv(example_file, header=TRUE)
if (data.use.sample==TRUE) data <- head(data, 10) # Just a sample
cat("Raw data:\n")
print(data)

#################################
# Example 1: Resolve mode
#################################

# Clear existing variables
suppressWarnings( rm( list = Filter( exists, c(response_vars, api_vars ) ) ) )

# Set options
mode <- "resolve"			# Processing mode

response <- get_request(url=url, mode=mode, data=data	)
if ( colnames(response)[1]=="error" ) {
	print( response )
} else {
	print(response)
	
	# More compact display:
	print(response[ , c("family", "species", "country", "state_province", "native_status", "native_status_reason", "native_status_sources")])
}

#################################
# Example 2: Country checklists
#################################

mode <- "country_checklists"		
rm( list = Filter( exists, response_vars ) )
country.checklists <- get_request(url=url, mode=mode)
country.checklists <- country.checklists[ order(country.checklists$gid_0), ]
print(country.checklists)

#################################
# Example 3: Checklist countries
#################################

mode <- "checklist_countries"		
rm( list = Filter( exists, response_vars ) )
checklist.countries <- get_request(url=url, mode=mode)
print(checklist.countries)
