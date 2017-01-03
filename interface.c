/**
 * -------------------------------------------------------------------
 * Nom du fichier : liste.c
 * @author  DESBIOLLES Hugo hugo.desbiolles@etu.univ-amu.fr, VILLA Gabriel gabriel.villa@etu.univ-amu.fr
 * Objet : Fonctions d'interface 
 * --------------------------------------------------------------------
*/


#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "interface.h"
#include "liste.h"

#define TAILLE 8
#define NBCASES 64
extern char othellier[TAILLE][TAILLE] ;
//----------------------COLORS --------------------
#define NORMALCOLOR  "\x1B[0m"
#define REDCOLOR  "\x1B[31m"
#define YELLOWCOLOR  "\x1B[33m"
#define BLUECOLOR  "\x1B[34m"



/**
 * Affiche l'othellier tel qu'il est
 */
void printGame(){		
	int i;
	//Affichage des num en haut
	for(i=0; i<TAILLE;i++){
		printf(" %c ", i+65);
	}
	
	for(i=0; i<NBCASES;i++){
		if(i%(TAILLE) == 0){
			if (i!=0){
				printf("%d",i/(TAILLE));
			}
			printf("\n");		
		}
		printf(" %c ",othellier[i/TAILLE][i%TAILLE]);	
	}
	printf("%d\n",TAILLE);
}


/**
 * Fonction qui affiche l'othellier avec les coups possibles
 * pour la couleur qui joue
 */
void printGameWithHelp(tpl cases){
	
	int i;
	//Affichage des num en haut
	for(i=0; i<TAILLE;i++){
		printf(" %c ",i+65);
	}
	
	for(i=0; i<NBCASES;i++){
		if(i%(TAILLE) == 0){
			if (i!=0){
				printf("%d",i/(TAILLE));
			}
			printf("\n");		
		}

		
		//Affichage en couleur d'un blanc(bleu) ou noir(rouge)
		if(othellier[i/TAILLE][i%TAILLE]=='N'){
			printf(" %sN%s ",BLUECOLOR,NORMALCOLOR);
		}else if(othellier[i/TAILLE][i%TAILLE]=='B'){
			printf(" %sB%s ",REDCOLOR,NORMALCOLOR);			
		}else{
			//Recherche si la case vide est jouable
			tpl searchResult = searchFor(i, cases);
			if(!est_vide(searchResult)){
				printf(" %sV%s ",YELLOWCOLOR,NORMALCOLOR);
			}else{
				printf(" V ");
			}
		}
	}
	printf("%d\n",TAILLE);
}


/**
 * Demande au joueur la case ou celui-ci veut jouer et teste si le joueur a le droit de jouer à cet endroit
 */
int askPlayer(tpl choix_possibles){
	int choix;
	//on répète tant que le choix n'est pas dans ceux proposés
	do{
		choix= humanInput();
		if(est_vide(searchFor(choix,choix_possibles)))
			printf("Tu n'as pas le droit de jouer ici, choisis une des cases colorées en jaune.\n");
	}while(est_vide(searchFor(choix,choix_possibles)));
	return choix;
}

/** 
 * Gère la syntaxe de l'entrée donnée par le joueur
 */
int humanInput(){
	char letter, number;
	do{
		printf("Choix (syntaxe : lettre Majuscule puis chiffre, ex : D5) : ");
		scanf(" %c%c",&letter,&number);
		fflush(stdin);
		
	}while((letter<65 ||letter>72) || (number<49 || number>57));
	
	return ((number-49)*TAILLE + (letter-65));
}

