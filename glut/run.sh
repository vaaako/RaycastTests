#!/bin/bash

NAME="NaldoRay-Alpha-v3"
DEBUG=""

# g++ -c main.cpp src/func.cpp -lsfml-graphics -lsfml-window -lsfml-system # Compile cpp files
# g++ main.o func.o -lsfml-graphics -lsfml-window -lsfml-system -o $NAME   # Compile to executable


if [ "${@: -1}"=="-d" ] || [ "${@: -1}"=="--debug" ]; then
	DEBUG="-g"
fi


g++ -c main.cpp src/*.cpp $DEBUG -lGL -lGLU -lglut -lm # Build cpp files
g++ *.o $DEBUG -lGL -lGLU -lglut -lm -o $NAME # Compile to executable



case "${@: -1}" in # Last argument
	-c | --compile)
		rm *.o # Compile
		;;
	-d | --debug)
		gdb $NAME
		;;
	*)
		./$NAME # Run
		rm $NAME *.o # Delete also program
esac
