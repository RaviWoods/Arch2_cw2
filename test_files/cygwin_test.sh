#!/bin/bash

FILETYPE=txt
TESTDIRECTORY=directmapped
SRCDIRECTORY=../source
INPUTFILENAME=input.txt
OUTPUTFILENAME=output.txt
PARAMSFILENAME=params.txt

INPUT=${TESTDIRECTORY}/${INPUTFILENAME}
OUTPUT=${TESTDIRECTORY}/${OUTPUTFILENAME}
PARAMS=${TESTDIRECTORY}/${PARAMSFILENAME}
TIME=$(date "+%H-%M-%S_%d-%m-%Y")

GOT=${TESTDIRECTORY}/got/${TESTDIRECTORY}_${TIME}.${FILETYPE}
touch ${GOT}

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
	g++ ${SRCDIRECTORY}/*.cpp -o ${SRCDIRECTORY}/memsim -std=c++11
	if [ -f ${PARAMS} ] 
	then
			cat ${INPUT}  |  ./${SRCDIRECTORY}/memsim ${PARAMSCONTENTS}  >  ${GOT}
			echo ${GOT}
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
   		sdiff --ignore-all-space ${GOT} ${OUTPUT}
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

 


