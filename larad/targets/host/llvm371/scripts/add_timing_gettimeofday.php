<?php

$sourcefile = $argv[1];	// Original C File

$fname = $argv[2]; // function name

// Loads original code from file
$code = file_get_contents($sourcefile);


# \S matches any non white space character
# \s matches any white space character
$patterns = array();
# Tested here: https://regex101.com/
$patterns[0] = '/(\s+main\s*\(.*\)\s*\{(.|\r|\n)*)('.$fname.'\s*\([^\;]*\)\;)(\s*)/';
$replacements = array();
$replacements[0] = '\1double t_start, t_end;\4t_start = timer_get();\4\3\4t_end = timer_get();\4printf ("\nelapsed: %0.6f\n", t_end - t_start);\4';

$data_code_wtiming = preg_replace($patterns, $replacements, $code);





$patterns[0] = '/(return\s+)([0-9]+)(\s*;)/';
$replacements = array();
$replacements[0] = 'printf("return: \2\n\n")\3 \1\2\3';	# two '\n' because otherwise the metric extractor will not work (why?)
#$data_code_wtiming = preg_replace($patterns, $replacements, $code);

$data_code_wtiming = preg_replace($patterns, $replacements, $data_code_wtiming);





$data_code_wtiming = "#include <sys/time.h>\n#include <stdio.h>\n\ndouble timer_get(){\n\tstruct timeval Tp;\n\tint stat;\n\tstat = gettimeofday (&Tp, NULL);\n\tif (stat != 0)\n\t\tprintf (\"Error return from gettimeofday: %d\", stat);\n\treturn (Tp.tv_sec + Tp.tv_usec * 1.0e-6);\n}\n\n" . $data_code_wtiming;

//$file_code_wtiming = 'code_timing.c';
//$fp = fopen($file_code_wtiming, "a") or die("Couldn't open $file for writing!");
//fwrite($fp, $data_code_wtiming_2) or die("Couldn't write values to file!");
//fclose($fp);
file_put_contents('main_wtiming.c', $data_code_wtiming);

?>
