#!/bin/bash

FILETYPE=txt
DIRECTORY=fullyassoc

INPUTFILENAME=input.txt
PARAMSFILENAME=params.txt

PARAMS=${DIRECTORY}/${PARAMSFILENAME}
GOT=${DIRECTORY}/got/INPUTFILENAME.${FILETYPE}
touch ${GOT}

clear
clear

if [ -f memsim ] 
	then
		rm memsim
fi
	
if [ -f ${PARAMS} ] 
	then
		PARAMSCONTENTS=$(<${PARAMS})
else
	echo "WRONG PARAMS NAME"
	exit 1
fi
	


if [ -f ${INPUT} ]
then
	g++ *.cpp -o memsim -std=c++11
	if [ -f ${PARAMS} ] 
	then
			cat ${INPUT}  |  ./memsim ${PARAMSCONTENTS} < ${GOT}
			echo "${GOT}"
	else 
		echo "NO PROGRAM COMPILATION"
		exit 1
	fi
else
	echo ${INPUT}
	echo "WRONG INPUT NAME"
	exit 1
fi

 


