main :	main.o liste.o
	gcc -o main main.o liste.o

liste.o : liste.c
	gcc -o liste.o -c liste.c -Wall

main.o : main.c liste.h
	gcc -o main.o -c main.c -Wall

clean:
	rm -rf *.o

mrproper: clean
	rm -rf hello
