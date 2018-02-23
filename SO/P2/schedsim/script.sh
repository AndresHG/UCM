
#! /bin/bash

existe=$false

echo "hola"

while [ ! $existe ]
do

	echo -n "Que fichero desea simular: "
	read archivo

	if [ -e examples ] ; 
	then
		cd examples
			if [ -e $archivo ] ; 
			then
				echo "Existe"
				existe=true
			else
				echo "No existe el archivo"
			fi
		cd ..
	else
		echo "No existe el directorio examples, creelo por favor, e introduzca en el mismo algunos ejemplos"
	fi

done

echo -n "Numero de CPU's: "
read cpu

while [ $cpu -gt 8 ]
do

	echo "Error al indroducir los CPU's, deben ser menos de 8"
	echo -n "Numero de CPU's: "
	read cpu

done

if [ ! -e resultados ] ;
then
	mkdir resultados
fi

for mode in RR SJF FCFS PRIO ;
do

	./schedsim -s $mode -n $cpu -i examples/$archivo 
	j=0
	while [ $j -lt $cpu ]
	do
		mv CPU_$j.log $mode-CPU-$j.log
		cp $mode-CPU-$j.log resultados
		rm $mode-CPU-$j.log
		cd ../gantt-gplot
		./generate_gantt_chart ../schedsim/resultados/$mode-CPU-$j.log
		cd ../schedsim
		let j+=1
	done

done









