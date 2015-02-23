#!/bin/bash
Objets="";

for j in `for i in src/*.c; do basename $i .c; done`
do 
	Objets="$Objets obj/$j.o"; 
done
