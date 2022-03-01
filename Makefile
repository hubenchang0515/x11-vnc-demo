# Generated by [MakeMake](https://github.com/hubenchang0515/makemake)

.PHONY: all install clean

all: X11-demo

install: all

clean:
	rm -f window.o main.o input.o

X11-demo : window.o main.o input.o  
	gcc -o $@ $^ -lvncserver -lxcb -lxcb-xtest -lxcb-keysyms 

window.o: window.c window.h
	gcc -c window.c -O3 

main.o: main.c window.h input.h
	gcc -c main.c -O3 

input.o: input.c input.h
	gcc -c input.c -O3 
