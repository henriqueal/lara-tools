<?php


$sourcefile = $argv[1];	// Original C File

$fname = $argv[2]; // function name

// Loads original code from file
$code = file_get_contents($sourcefile);




# \S matches any non white space character
# \s matches any white space character
$patterns = array();
# Tested here: https://regex101.com/
$patterns[0] = '/#pragma monitor start/';
$patterns[1] = '/#pragma monitor stop/';
$replacements = array();
$replacements[0] = 'struct timespec t_start, t_stop;\4clock_gettime( CLOCK_MONOTONIC, &t_start);';
$replacements[1] = 'clock_gettime( CLOCK_MONOTONIC, &t_stop);\4printf ("\nelapsed: %0.6f\n", (float) (( t_stop.tv_sec - t_start.tv_sec ) + ( t_stop.tv_nsec - t_start.tv_nsec ) / 1000000000.0));';

$data_code_wtiming = preg_replace($patterns, $replacements, $code);





$patterns[0] = '/(return\s+)([0-9]+)(\s*;)/';
$replacements = array();
$replacements[0] = 'printf("return: \2\n\n")\3 \1\2\3';	# two '\n' because otherwise the metric extractor will not work (why?)
#$data_code_wtiming = preg_replace($patterns, $replacements, $code);

$data_code_wtiming = preg_replace($patterns, $replacements, $data_code_wtiming);





$data_code_wtiming = "#include <time.h>\n#include <stdio.h>\n\n" . $data_code_wtiming;

//$file_code_wtiming = 'code_timing.c';
//$fp = fopen($file_code_wtiming, "a") or die("Couldn't open $file for writing!");
//fwrite($fp, $data_code_wtiming_2) or die("Couldn't write values to file!");
//fclose($fp);
file_put_contents('main_wtiming.c', $data_code_wtiming);

?>

