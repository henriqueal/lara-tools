<?php

$sourcefile = $argv[1];	// Original C File

// Loads original code from file
$code = file_get_contents($sourcefile);


$patterns = array();
$patterns[0] = '/([\r|\n|\s]main\s*\(.*\)[\r|\n|\s]*\{)([\r|\n|\s]*)/';
$replacements = array();
$replacements[0] = '\1\2double t_start, t_end;\2t_start = timer_get();\2\2';

$data_code_wtiming = preg_replace($patterns, $replacements, $code);


$patterns[0] = '/([\r|\n|\s]main\s*\(.*\)[\r|\n|\s]*\{[\s|\S]*)([\r|\n|\s]*)(return[\r|\n|\s|\;])/';
$replacements[0] = '\1\2t_end = timer_get();\2printf ("\n%0.6f\n", t_end - t_start);\2\3';

$data_code_wtiming_2 = preg_replace($patterns, $replacements, $data_code_wtiming);


// If no change was made means that the main function has no 'return' statement.
if(strcmp($data_code_wtiming, $data_code_wtiming_2) == 0) {
	//echo "\nmain() has no return statement.\n";
        $patterns[0] = '/([\r|\n|\s]main\s*\(.*\)[\r|\n|\s]*\{)([\r|\n|\s]*)([\s|\S]*)(\})/';
        $replacements[0] = '\1\2\3\2t_end = timer_get();\2printf ("\n%0.6f\n", t_end - t_start);\2\4';
       	$data_code_wtiming_2 = preg_replace($patterns, $replacements, $data_code_wtiming);


}

$data_code_wtiming_2 = "#include <sys/time.h>\n#include<stdio.h>\n\ndouble timer_get(){\nstruct timeval Tp;\nint stat;\nstat = gettimeofday (&Tp, NULL);\nif (stat != 0)\nprintf (\"Error return from gettimeofday: %d\", stat);\nreturn (Tp.tv_sec + Tp.tv_usec * 1.0e-6);\n}\n\n" . $data_code_wtiming_2;

//$file_code_wtiming = 'code_timing.c';
//$fp = fopen($file_code_wtiming, "a") or die("Couldn't open $file for writing!");
//fwrite($fp, $data_code_wtiming_2) or die("Couldn't write values to file!");
//fclose($fp);
file_put_contents('code_timing.c', $data_code_wtiming_2);

?>
