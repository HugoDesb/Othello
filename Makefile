#---------------------------------------------------------------
# Nom du fichier : makefile
# @author  DESBIOLLES Hugo hugo.desbiolles@etu.univ-amu.fr, VILLA Gabriel gabriel.villa@etu.univ-amu.fr
# Objet : Commandes de compilation du programme othello 
# Pour generer l'executable (main) : tapez "make" 
# Pour effacer les fichiers objet et l'executable : tapez "make clean"
#--------------------------------------------------------------------


main :	main.o liste.o interface.o calcul.o
	gcc -o main main.o liste.o interface.o calcul.o

main.o : main.c liste.h
	gcc -o main.o -c main.c -Wall

liste.o : liste.c
	gcc -o liste.o -c liste.c -Wall

interface.o : interface.c liste.h
	gcc -o interface.o -c interface.c -Wall

calcul.o : calcul.c liste.h
	gcc -o calcul.o -c calcul.c -Wall

clean:
	rm -rf *.o

mrproper: clean
	rm -rf hello
