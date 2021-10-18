#!/usr/bin/perl
#Algoritmo3
# Fichero para automatización de ejecución por lotes de un ejecutable
# dado parámetros de entrada.
# $ --> variable
# @ --> vector
$repeticiones =30;
@ejecutables = ("matricesApp");
@matrizSize = ("100","200","400","800","1000","1200","2000","4000");
@cores=("1","2","4","6","8");
$path = "/Users/valentinagomez/projects/ParcialUno/Algorirmo3/";

foreach $exe (@ejecutables) {
	foreach $size (@matrizSize) {
	  foreach $core (@cores){
		$fichero = "$path"."Soluciones/"."$exe"."-size"."$size"."-Core"."$core";
		#print("$fichero\n");
		for ($i=0; $i<$repeticiones; $i++) {
			#print("$path$exe $size\n");
			system("$path$exe $size $core >> $fichero");

		}
	   }
	}
}
exit(1);
