all: buscar

buscar: buscar.o
	gcc -o buscar buscar.o

buscar.o: buscar.c
	gcc -c buscar.c
clean:
	rm -f buscar *.o
