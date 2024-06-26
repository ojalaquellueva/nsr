<?php

function parseArgs( $args ) {
	// Required for parsing php cli arguments in format -foo=bar
	// Parses the php $argv object (=$args)
	// See also: getArg
	foreach( $args as $arg ) {
		$tmp = explode( '=', $arg, 2 );
		if( $arg[0] == "-" ) {
			$args[ substr( $tmp[0], 1 ) ] = $tmp[1];
		}
	}
	return $args;
}
 
function getArg( $args, $arg ) {
	// Required for parsing php cli arguments in format -foo=bar
	// Run after parseArgs
	// see also: parseArgs
	if( isset( $args[$arg] ) ) {
		return $args[$arg];
	}
	return false;
}

function confirm($confmsg) {
	// displays confirmation message, accepts yes/no response
	// causes die if any response other than yes
	
	// Ask user if wants to continue
	fwrite(STDOUT, $confmsg);
	$response = trim(fgets(STDIN));

	if (!(strtolower($response)=="y"||strtolower($response)=="yes")) {
		die("Operation cancelled");
	} else {
		return true;
	}
}

function responseYesNoDie($confmsg) {
	// Accepts yes/no response, returns true/false
	// Dies if any response other than yes or no
	
	// Ask user if wants to continue
	fwrite(STDOUT, $confmsg.' ');
	$response = trim(fgets(STDIN));

	if (strtolower($response)=="y"||strtolower($response)=="yes") {
		return true;
	} elseif (strtolower($response)=="n"||strtolower($response)=="no") {
		return false;
	} else {
		die("Please repond yes or no\r\n");
	}
}



function ext2ascii($str) {
	// Converts extended ascii characters to plain ascii equivalents
	// Essentially, converts accented characters to non-accented
	$arr=array(
	  chr(161)=>'A', chr(163)=>'L', chr(165)=>'L', chr(166)=>'S', chr(169)=>'S',
	  chr(170)=>'S', chr(171)=>'T', chr(172)=>'Z', chr(174)=>'Z', chr(175)=>'Z',
	  chr(177)=>'a', chr(179)=>'l', chr(181)=>'l', chr(182)=>'s', chr(185)=>'s',
	  chr(186)=>'s', chr(187)=>'t', chr(188)=>'z', chr(190)=>'z', chr(191)=>'z',
	  chr(192)=>'R', chr(193)=>'A', chr(194)=>'A', chr(195)=>'A', chr(196)=>'A',
	  chr(197)=>'L', chr(198)=>'C', chr(199)=>'C', chr(200)=>'C', chr(201)=>'E',
	  chr(202)=>'E', chr(203)=>'E', chr(204)=>'E', chr(205)=>'I', chr(206)=>'I',
	  chr(207)=>'D', chr(208)=>'D', chr(209)=>'N', chr(210)=>'N', chr(211)=>'O',
	  chr(212)=>'O', chr(213)=>'O', chr(214)=>'O', chr(216)=>'R', chr(217)=>'U',
	  chr(218)=>'U', chr(219)=>'U', chr(220)=>'U', chr(221)=>'Y', chr(222)=>'T',
	  chr(223)=>'s', chr(224)=>'r', chr(225)=>'a', chr(226)=>'a', chr(227)=>'a',
	  chr(228)=>'a', chr(229)=>'l', chr(230)=>'c', chr(231)=>'c', chr(232)=>'c',
	  chr(233)=>'e', chr(234)=>'e', chr(235)=>'e', chr(236)=>'e', chr(237)=>'i',
	  chr(238)=>'i', chr(239)=>'d', chr(240)=>'d', chr(241)=>'n', chr(242)=>'n',
	  chr(243)=>'o', chr(244)=>'o', chr(245)=>'o', chr(246)=>'o', chr(248)=>'r',
	  chr(249)=>'u', chr(250)=>'u', chr(251)=>'u', chr(252)=>'u', chr(253)=>'y',
	  chr(254)=>'t'
	);
 return strtr($str,$arr);
}

function iso2text($str) {
	// Replaces html-formated iso codes with the actual character
	// Html iso codes begin with "&#" and end with ";", e.g., "&#213;"
	$start=strpos($str,"&#");
	$len=strlen($str);
	if ($start>=0 && $start<$len) {
		// possible isocode

		// check for termination semi-colon
		if (substr($str,$start+4,1)==";") {
			// Two-digit ascii?
			// Check the number
			$isocode=substr($str,$start+1,2);
			
			if (is_numeric($isocode)) {
				$new=chr($isocode);
				$old="&#$isocode;";
				//echo "str1=$str, old=$old, new=$new, isocode=$isocode\r\n";
				$fixed=str_replace($old,$new,$str);
				return $fixed;
			} else {
				return $str;
			}
		} elseif  (substr($str,$start+5,1)==";") {
			// 3-digit ascii code?
			// Check the number
			$isocode=substr($str,$start+2,3);

			if (is_numeric($isocode)) {
				$new=chr($isocode);
				$old="&#$isocode;";
				//echo "str2=$str, old=$old, new=$new, isocode=$isocode\r\n";
				$fixed=str_replace($old,$new,$str);
				return $fixed;
			} else {
				return $isocode;
			}
		} else {
			return $str;
		}
		
	} else {
		return $str;
	}
}

function htmliso2text($str) {
	// Converts html iso codes to actual characters
	// Mostly alphabetic characters and numbers only
	$arr=array(
		'&#48;'=>'0',
		'&#49;'=>'1',
		'&#50;'=>'2',
		'&#51;'=>'3',
		'&#52;'=>'4',
		'&#53;'=>'5',
		'&#54;'=>'6',
		'&#55;'=>'7',
		'&#56;'=>'8',
		'&#57;'=>'9',
		'&#58;'=>':',
		'&#59;'=>';',
		'&#60;'=>'<',
		'&#61;'=>'=',
		'&#62;'=>'>',
		'&#63;'=>'?',
		'&#64;'=>'@',
		'&#65;'=>'A',
		'&#66;'=>'B',
		'&#67;'=>'C',
		'&#68;'=>'D',
		'&#69;'=>'E',
		'&#70;'=>'F',
		'&#71;'=>'G',
		'&#72;'=>'H',
		'&#73;'=>'I',
		'&#74;'=>'J',
		'&#75;'=>'K',
		'&#76;'=>'L',
		'&#77;'=>'M',
		'&#78;'=>'N',
		'&#79;'=>'O',
		'&#80;'=>'P',
		'&#81;'=>'Q',
		'&#82;'=>'R',
		'&#83;'=>'S',
		'&#84;'=>'T',
		'&#85;'=>'U',
		'&#86;'=>'V',
		'&#87;'=>'W',
		'&#88;'=>'X',
		'&#89;'=>'Y',
		'&#90;'=>'Z',
		'&#91;'=>'[',
		'&#93;'=>']',
		'&#94;'=>'^',
		'&#95;'=>'_',
		'&#96;'=>'`',
		'&#97;'=>'a',
		'&#98;'=>'b',
		'&#99;'=>'c',
		'&#100;'=>'d',
		'&#101;'=>'e',
		'&#102;'=>'f',
		'&#103;'=>'g',
		'&#104;'=>'h',
		'&#105;'=>'i',
		'&#106;'=>'j',
		'&#107;'=>'k',
		'&#108;'=>'l',
		'&#109;'=>'m',
		'&#110;'=>'n',
		'&#111;'=>'o',
		'&#112;'=>'p',
		'&#113;'=>'q',
		'&#114;'=>'r',
		'&#115;'=>'s',
		'&#116;'=>'t',
		'&#117;'=>'u',
		'&#118;'=>'v',
		'&#119;'=>'w',
		'&#120;'=>'x',
		'&#121;'=>'y',
		'&#122;'=>'z',
		'&#123;'=>'{',
		'&#124;'=>'|',
		'&#125;'=>'}',
		'&#126;'=>'~',
		'&#192;'=>'�',
		'&#193;'=>'�',
		'&#194;'=>'�',
		'&#195;'=>'�',
		'&#196;'=>'�',
		'&#197;'=>'�',
		'&#198;'=>'�',
		'&#199;'=>'�',
		'&#200;'=>'�',
		'&#201;'=>'�',
		'&#202;'=>'�',
		'&#203;'=>'�',
		'&#204;'=>'�',
		'&#205;'=>'�',
		'&#206;'=>'�',
		'&#207;'=>'�',
		'&#208;'=>'�',
		'&#209;'=>'�',
		'&#210;'=>'�',
		'&#211;'=>'�',
		'&#212;'=>'�',
		'&#213;'=>'�',
		'&#214;'=>'�',
		'&#216;'=>'�',
		'&#217;'=>'�',
		'&#218;'=>'�',
		'&#219;'=>'�',
		'&#220;'=>'�',
		'&#221;'=>'�',
		'&#222;'=>'�',
		'&#223;'=>'�',
		'&#224;'=>'�',
		'&#225;'=>'�',
		'&#226;'=>'�',
		'&#227;'=>'�',
		'&#228;'=>'�',
		'&#229;'=>'�',
		'&#230;'=>'�',
		'&#231;'=>'�',
		'&#232;'=>'�',
		'&#233;'=>'�',
		'&#234;'=>'�',
		'&#235;'=>'�',
		'&#236;'=>'�',
		'&#237;'=>'�',
		'&#238;'=>'�',
		'&#239;'=>'�',
		'&#240;'=>'�',
		'&#241;'=>'�',
		'&#242;'=>'�',
		'&#243;'=>'�',
		'&#244;'=>'�',
		'&#245;'=>'�',
		'&#246;'=>'�',
		'&#248;'=>'�',
		'&#249;'=>'�',
		'&#250;'=>'�',
		'&#251;'=>'�',
		'&#252;'=>'�',
		'&#253;'=>'�',
		'&#254;'=>'�',
		'&#255;'=>'�'
	);
 return strtr($str,$arr);
}

class Latin1UTF8 {
   
    private $latin1_to_utf8;
    private $utf8_to_latin1;
    public function __construct() {
        for($i=32; $i<=255; $i++) {
            $this->latin1_to_utf8[chr($i)] = utf8_encode(chr($i));
            $this->utf8_to_latin1[utf8_encode(chr($i))] = chr($i);
        }
    }
   
    public function mixed_to_latin1($text) {
        foreach( $this->utf8_to_latin1 as $key => $val ) {
            $text = str_replace($key, $val, $text);
        }
        return $text;
    }

    public function mixed_to_utf8($text) {
        return utf8_encode($this->mixed_to_latin1($text));
    }
}

function secondsToTime($s) {
	/////////////////////////////////////////////////////////
	// Converts seconds to hours:minutes:seconds 
	// 
	// If you don't want to display the numbers after the 
	// decimal, just add round($s); to the beginning
	/////////////////////////////////////////////////////
	
    $h = floor($s / 3600);
    $s -= $h * 3600;
    $m = floor($s / 60);
    $s -= $m * 60;
    return $h.':'.sprintf('%02d', $m).':'.sprintf('%02d', $s);
}

function array_to_csv($arr,$delim) {
	#############################################
	# Converts nested array $arr to a csv 'table array',
	# with each row a single delimited string,
	# and column cells separated by delimiter $delim.
	# Assumes first row is header
	#
	# Requires functions:
	#	csv_header
	#	csv_row
	#############################################

	# Extract header
	$header = csv_header($arr,$delim);
	$header = preg_split("/[\f\r\n]+/",$header ); # convert string to array
	$header = array_unique($header);	# get unique lines
	$header = implode("", $header);	# convert back to string
	
	# Extract cells
	$rows = csv_rows($arr,$delim);
	$rows = preg_replace("/(^[\r\n]*|[\r\n]+)[\s\t]*[\r\n]+/", "\n", $rows);
	
	# Combine header and table
	$table = $header . "\n" . $rows;
	return($table);
}

function csv_header($arr,$delim) { 
	# Extract  ultimate elements header
	$return = "";
	
	foreach ($arr as $key => $value) {
	//$return .= "$key: ";
		if (is_array($value)) {
			$return .= csv_header($value,$delim);
		} else {
			$return .= $key.$delim;
		}
		$return .= "";
	}
	
	$return = rtrim(trim($return), $delim);
	$return .= "\n";
	return($return);
}

function csv_rows($arr,$delim) {
	# Accumulate ultimate elements values as row
	$return = "";

	foreach ($arr as $key => $value) {
		if (is_array($value)) {
			$return .= csv_rows($value,$delim);
		} else {
			# Convert double quotes, if any, to single quotes
			if ( preg_match('/"/', $value) == 1 ) {
				$value = str_replace('"', "'", $value);
			}
			
			# Wrap in double quotes if comma(s) present
			if( strpos($value, ",") !== false ) {
				$value = "\"" . $value . "\"";
			}
			
			$return .= $value.$delim;
		}
		$return .= "";
	}
	
	$return = rtrim(trim($return), $delim);
	$return .= "\n";
	return($return);
}





?>
