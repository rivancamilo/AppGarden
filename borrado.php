<?php

ini_set ('error_reporting', E_ALL & ~E_NOTICE);



for($i=1;$i<5;$i++){
    $filename=("v".$i.".json");
    unlink($filename); // Delete the file
    $fpst = fopen($filename,"w"); // $fp is now the file pointer to file $filename
    if($fpst){
    	fwrite($fpst,"");
    }
    
    else{
    	echo $filename . " was not initialized successfully.";
    }
    
    fclose($fpst);
}
    echo "Exito";

?>





