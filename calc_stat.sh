#!/bin/bash

#checking if the number of argument is exactly one
if [ "$#" -ne 1 ]; then
    echo wrong number of argument >&2
    exit
fi

#checking if the file exists
if [[! -f $1.txt]]; then
    echo course not found >&2
    exit
fi

#checking if there is existing directory already and creat if not
if [[ -e $1_stat]]; then
 rmdir $1_stat
fi

#delet the file if it's already exist
if [[! -e $1_stat]]; then
 mkdir $1_stat
 fi
 
 cat $1.txt|hist.c|histogram.txt

$ cat > statistics.txt
cat $1.txt|mean.c|statistics.txt
cat $1.txt|min.c|statistics.txt
cat $1.txt|max.c|statistics.txt
cat $1.txt|median.c|statistics.txt

num_of_students=0;
num_of_pass_students=0;
num_of_lines=0;
pass_percent=0;

#calculate the percent of pass students
for j in $(awk '{print $2;}' ./$1_stat/hist.txt); do
   num_of_students=$(echo $num_of_students+$j| bc)
   ((num_of_lines++))
   if[[num_of_lines -gt 55]]; then
   num_of_pass_students=$(echo $num_of_pass_students+$j| bc)
   fi
done
((pass_percent=100*num_of_pass_students/num_of_students))
echo -n -e "$pass_percent" >> ./$1_stat/statistics.txt
   
   
