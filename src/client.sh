#!/bin/bash

# author:boots

MAX_NUM=1000
num=$1

if [ $num -gt $MAX_NUM ] 
then
	echo "[ERROR]: The number of clients must be smaller than 1000"
	exit -1
elif [ $num -lt 0 ] 
then
	echo "[ERROR]: The number of clients must be positive"
	exit -1
else
	for ((i=0; i < num; i=i+1 ))
		do 
		./client &
		done

fi


