#!/bin/bash

# a) Copie dos ficheros de texto que ocupen más de un boque (por ejemplo fuseLib.c y
#    myFS.h) a nuestro SF y a un directorio temporal, por ejemplo ./temp

if test -e ./mount-point; then
	rm -r ./mount-point
fi

if test -e ./temp; then
	rm -r ./temp
fi

mkdir ./temp
mkdir ./mount-point

touch ./mount-point/p4.txt
touch ./mount-point/nada.txt

echo "Comprobando funcionalidad del sistema de archivos" > ./mount-point/p4.txt

ls ./mount-point

cp ./mount-point/p4.txt  ./temp

diff ./temp/p4.txt ./mount-point/p4.txt > ./mount-point/nada.txt

if [[ -s ./mount-point/nada.txt ]] ; then
echo "File nada.txt has data."
else
rm -r ./mount-point/nada.txt
fi ;
