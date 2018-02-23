#!/bin/bash

MPOINT="./mount-point"
TEMPDIR="./temporal"
FILE1="./src/fuseLib.c"
FILE1NAME="fuseLib.c"
FILE2="./src/myFS.h"
FILE2NAME="myFS.h"
FILE3="./fichero3.txt"
FILE3NAME="fichero3.txt"
AUDITA="./my-fsck"
DISCOV="./virtual-disk"
BLOCKSIZE=4096
VACIO=""

#A
echo "--> Copiando ficheros $FILE1NAME y $FILE2NAME en $MPOINT "
cp $FILE1 $FILE2 $MPOINT/

if [ ! -d $TEMPDIR ]; then
	echo "--> Creando carpeta $TEMPDIR"
	mkdir $TEMPDIR
fi
echo "--> Copiando ficheros $FILE1NAME y $FILE2NAME en $TEMPDIR "
cp $FILE1 $FILE2 $TEMPDIR
read -p "------>Pulsa Enter"

#B
echo "--> Auditando el disco $DISCOV"
$AUDITA $DISCOV

echo "--> Ejecutando diff sobre $FILE1NAME y $FILE2NAME en $MPOINT y ./"
DIFF1=$(diff $MPOINT/$FILE1NAME $FILE1)
if [[ $DIFF1 == $VACIO ]]; then 
	echo "---->Diff de $FILE1NAME : ficheros iguales" 
else
	echo "---->Diff de $FILE1NAME : ficheros diferentes"
fi
DIFF2=$(diff $MPOINT/$FILE2NAME $FILE2)
if [[ $DIFF2 == $VACIO ]]; then 
	echo "---->Diff de $FILE2NAME : ficheros iguales" 
else
	echo "---->Diff de $FILE2NAME : ficheros diferentes"
fi
read -p "------>Pulsa Enter"

#C
echo "--> Elaborando nuevo tamaño de ficheros $FILE1NAME"
FILE1SIZE=$(stat -c%s "$FILE1")

NEWSIZE1=`expr $FILE1SIZE - $BLOCKSIZE`
echo "---->Nuevo tamaño: $NEWSIZE1"

echo "--> Truncando $TEMPDIR/$FILE1NAME"
truncate --size=$NEWSIZE1 $TEMPDIR/$FILE1NAME

echo "--> Truncando $MPOINT/$FILE1NAME"
truncate --size=$NEWSIZE1 $MPOINT/$FILE1NAME

read -p "------>Pulsa Enter"

#D
echo "--> Auditando el disco $DISCOV"
$AUDITA $DISCOV

echo "--> Ejecutando diff sobre $FILE1NAME en $MPOINT y ./"
DIFF1=$(diff $MPOINT/$FILE1NAME $FILE1)
if [[ $DIFF1 == $VACIO ]]; then 
	echo "---->Diff de $FILE1NAME : ficheros iguales" 
else
	echo "---->Diff de $FILE1NAME : ficheros diferentes"
fi
read -p "------>Pulsa Enter"

#E
echo "--> Creando fichero3.txt"
echo "tercer fichero, de texto, para el script" > $FILE3
echo "--> Copiando el fichero3.txt a $MPOINT"
cp $FILE3 $MPOINT/

read -p "------>Pulsa Enter"

#F
echo "--> Auditando el disco $DISCOV"
$AUDITA $DISCOV

echo "--> Ejecutando diff sobre $FILE3NAME en $MPOINT y ./"
DIFF3=$(diff $MPOINT/$FILE3NAME $FILE3)
if [[ $DIFF3 == $VACIO ]]; then 
	echo "---->Diff de $FILE3NAME : ficheros iguales" 
else
	echo "---->Diff de $FILE3NAME : ficheros diferentes"
fi
read -p "------>Pulsa Enter"

#G
echo "--> Elaborando nuevo tamaño de fichero $FILE2"
FILE2SIZE=$(stat -c%s "$FILE2")

NEWSIZE2=`expr $FILE2SIZE + $BLOCKSIZE`
echo "---->Nuevo tamaño : $NEWSIZE2"

echo "--> Truncando $TEMPDIR/$FILE2NAME"
truncate --size=$NEWSIZE2 $TEMPDIR/$FILE2NAME

echo "--> Truncando $MPOINT/$FILE2NAME"
truncate --size=$NEWSIZE2 $MPOINT/$FILE2NAME

read -p "------>Pulsa Enter"

#H
echo "--> Auditando el disco $DISCOV"
$AUDITA $DISCOV

echo "--> Ejecutando diff sobre $FILE2NAME en $MPOINT y ./"
DIFF2=$(diff $MPOINT/$FILE2NAME $FILE2)
if [[ $DIFF2 == $VACIO ]]; then 
	echo "---->Diff de $FILE2NAME : ficheros iguales" 
else
	echo "---->Diff de $FILE2NAME : ficheros diferentes"
fi
read -p "------>Pulsa Enter"