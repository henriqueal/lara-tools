<?php

$sourcefile = $argv[1]; // Original C File

#$fname = $argv[2]; // function name

// Loads original code from file
$code = file_get_contents($sourcefile);



$patterns[0] = '/(return\s+)([0-9]+)(\s*;)/';
$replacements = array();
$replacements[0] = 'printf("return: \2\n\n")\3 \1\2\3'; # two '\n' because otherwise the metric extractor will not work (why?)
#$data_code_wtiming = preg_replace($patterns, $replacements, $code);

$data_code_wtiming = preg_replace($patterns, $replacements, $code);





$data_code_wtiming = "#include <stdio.h>\n\n" . $data_code_wtiming;

//$file_code_wtiming = 'code_timing.c';
//$fp = fopen($file_code_wtiming, "a") or die("Couldn't open $file for writing!");
//fwrite($fp, $data_code_wtiming_2) or die("Couldn't write values to file!");
//fclose($fp);
file_put_contents('main_wtiming.c', $data_code_wtiming);

?>

