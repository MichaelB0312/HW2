#!/bin/bash

#checking if the number of argument is exactly one
if [[ ! $# -eq 1 ]]; then
	echo Wrong number of arguments >&2
	exit
fi
#checking if the file exists
if [[ ! -f $1.txt ]]; then
	echo Course not found >&2
	exit
fi
#checking if there is existing directory already
if [[ -e $1_stat ]]; then
	rmdir $1_stat
fi
#creating new directory and creating the grade file
mkdir $1_stat
awk 'NR>1 {print $2}' $1.txt > ./$1_stat/grades.txt

#compiling the c program
gcc -c -g -Wall calc_statistics.c
gcc -o prog.exe calc_statistics.o

#running the program and passing the relevant paths as arguments
./prog.exe ./$1_stat/grades.txt ./$1_stat/course_statistics.txt

#printing the statistics file as requested
cat ./$1_stat/course_statistics.txt
