all: ebbandflow

ebbandflow: main.c
	gcc main.c -o build/ebbandflow -lraylib

run: ebbandflow
	build/ebbandflow
