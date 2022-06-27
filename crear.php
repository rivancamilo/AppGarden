<?php

ini_set('error_reporting', E_ALL & ~E_NOTICE);

//a=m&v=1&s=1&t=8&d=0&h=13
//ON*1*m*0-0-0-0-0-0-0*0
$metodo = $_POST["a"];
$val    = $_POST["v"];
$st     = $_POST["s"];
$tim    = $_POST["t"];
$dia    = $_POST["d"];
$hora   = $_POST["h"];

$v=explode("-", $dia);



$filename = "v" . $val . ".json";
unlink($filename); // Delete the file
$fp = fopen($filename, "a"); // $fp is now the file pointer to file $filename


if ($fp) {
    
    if ($metodo == "m") {
        
        if ($st == "1") {
            fwrite($fp, "ON");
            
            if (((int) $tim) >= 1 and ((int) $tim) <= 30) {
                fwrite($fp, "*" . $tim . "*m*0-0-0-0-0-0-0*0");
            } else {
                fwrite($fp, "*1*m*0-0-0-0-0-0-0*0");
            }
            
        } else if ($st == "0") {
            fwrite($fp, "OFF");
            fwrite($fp, "*10*m*0-0-0-0-0-0-0*0");
            
        }
        
    } else if ($metodo == "a") {
        
        if ($st == "1") {
            fwrite($fp, "ON");
            
            if (((int) $tim) >= 1 and ((int) $tim) <= 30) {
                fwrite($fp, "*" . $tim . "*a*");
                
            } else {
                fwrite($fp, "*1*a*");
            }

            if (((int) $dia) >= 0 and ((int) $dia) <= 2) {
                fwrite($fp, "".$dia."*");
            } else {
                fwrite($fp, "0*");
            }
            
            if (((int) $hora) >= 0 and ((int) $hora) <= 23) {
                fwrite($fp, "".$hora."");
            } else {
                fwrite($fp, "12");
            }
            
        } 
    }
    
} else {
    echo $filename . " was not initialized successfully.";
}


fclose($fp);

echo "Modo: " . $metodo;
echo " - Valvula: " . $val;
echo " - Estado: " . $st;
echo " - Tiempo: " . $tim;
echo " - Hora: " . "$hora";
echo " - Dias: ";
echo $v[0]; //
echo " - ";
echo $v[1]; 
echo " - ";
echo $v[2]; //
echo " - ";
echo $v[3];
echo " - ";
echo $v[4]; //
echo " - ";
echo $v[5];
echo " - ";
echo $v[6]; //

?>


