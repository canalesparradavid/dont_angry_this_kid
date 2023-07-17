.SILENT:

CFLAGS = -lssl -lcrypto -Wno-deprecated-declarations -Wno-format-zero-length

all: init main

init:
	mkdir -p bin

main: ./src/main.c comparator
	gcc ./src/main.c ./bin/CodeComparator.o -o ./bin/main $(CFLAGS)

comparator: ./src/CodeComparator.h ./src/CodeComparator.c
	gcc ./src/CodeComparator.c -c -o ./bin/CodeComparator.o $(CFLAGS)

clear:
	rm -rf bin
