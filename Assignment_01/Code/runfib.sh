#!/bin/bash
gcc fib.c -o $1
for ((i=0;i<$2;i++))
do
 ./$1 2 5 6
done 
