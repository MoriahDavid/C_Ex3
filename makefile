.PHONY: all clean

all: main.c stringProg

stringProg: main.c
	gcc -Wall main.c -o stringProg

clean:
	rm -f stringProg