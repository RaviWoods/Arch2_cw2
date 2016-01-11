#!/bin/bash

FILETYPE=txt
DIRECTORY=directmapped

INPUTFILENAME=input.txt
OUTPUTFILENAME=output.txt
PARAMSFILENAME=params.txt

INPUT=${DIRECTORY}/${INPUTFILENAME}
OUTPUT=${DIRECTORY}/${OUTPUTFILENAME}
PARAMS=${DIRECTORY}/${PARAMSFILENAME}
TIME=$(date "+%H-%M-%S_%d-%m-%Y")

GOT=${DIRECTORY}/got/${DIRECTORY}_${TIME}.${FILETYPE}
touch ${GOT}
clear
killall -9 FileMerge
if [ -f memsim ] 
	then
		rm memsim
fi
	
if [ -f ${PARAMS} ] 
	then
		PARAMSCONTENTS=$(<${PARAMS})
else
	echo "WRONG PARAMS NAME"
	rm ${GOT}
	exit 1
fi
	


if [ -f ${INPUT} ]
then
	g++ *.cpp -o memsim -std=c++11
	if [ -f ${PARAMS} ] 
	then
			cat ${INPUT}  |  ./memsim ${PARAMSCONTENTS}  >  ${GOT}
	else 
		echo "NO PROGRAM COMPILATION"
		rm ${GOT}
		exit 1
	fi
else
	echo ${INPUT}
	echo "WRONG INPUT NAME"
	rm ${GOT}
	exit 1
fi

if [ -s ${GOT} ]
then	
	if [ -f ${OUTPUT} ]
	then
   		opendiff ${GOT} ${OUTPUT}
		exit 1
	else 
		echo "WRONG OUTPUT NAME"	
		rm ${GOT}
		exit 0
	fi
else
	echo "NO PROGRAM OUTPUT"
	rm ${GOT}
	exit 0
fi

 


