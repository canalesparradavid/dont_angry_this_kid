.SILENT:

CFLAGS = -lssl -lcrypto -Wno-deprecated-declarations -Wno-format-zero-length

all: init main

build: all
	echo "Guardando programa."
	mkdir -p build
	mv ./bin/main ./build/datk
	make --no-print-directory clear

init:
	mkdir -p bin

main: ./src/main.c modules
	echo "Compilando programa principal."
	gcc ./src/main.c ./bin/CodeComparator.o -o ./bin/main $(CFLAGS)

modules: comparator
	echo "Modulos compilados."

comparator: ./src/CodeComparator.h ./src/CodeComparator.c
	echo "Compilando el comparador de directorios."
	gcc ./src/CodeComparator.c -c -o ./bin/CodeComparator.o $(CFLAGS)

clear:
	echo "Eliminando carpeta de binarios."
	rm -rf bin
