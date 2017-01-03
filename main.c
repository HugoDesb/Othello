/** 
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

/**
 * @author DESBIOLLES Hugo hugo.desbiolles@etu.univ-amu.fr, VILLA Gabriel gabriel.villa@etu.univ-amu.fr
 */

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "liste.h"
#include "interface.h"
#include "calcul.h"
#include <stdlib.h>


#define TAILLE 8
#define NBCASES 64

int main();  	
void initialization();	
void playing();		
void endGame();		

char othellier[TAILLE][TAILLE] ;


int main(){
	initialization();
	playing();
	endGame();
	return 0;
}


void initialization(){		
	int i;
	for(i=0; i<NBCASES;i++){
		if(i==27 || i==36){
			othellier[i/8][i%8] = 'N';
		}else if(i==28 || i==35){
			othellier[i/8][i%8] = 'B';
		}else{
			othellier[i/8][i%8] = 'V';
		}
	}
}


void playing(){
	int playerNok = 1,playerBok = 1;
	int choix,count = 4;
	tpl choix_possibles;
	while((playerNok || playerBok) && count<64){
		playerNok = 1;
		playerBok = 1;
		
			//Joueur Noir
		choix_possibles = coup_jouable('N');
		if(!est_vide(choix_possibles)){
			printf("Les noirs jouent.\n");
			printGameWithHelp(choix_possibles);
			choix = askPlayer(choix_possibles);
			change_othellier(choix,'N');
			count++;
		}else{
			printf("Désolé, tu ne peux pas jouer!\n");
			playerNok = 0;
		}
	
			//Joueur Blanc
		choix_possibles = coup_jouable('B');
		if(!est_vide(choix_possibles)){
			printf("Les blancs jouent.\n");
			printGameWithHelp(choix_possibles);
			choix = askPlayer(choix_possibles);
			change_othellier(choix,'B');
			count++;
		}else{
			printf("Désolé, tu ne peux pas jouer!\n");
			playerBok = 0;
		}
	}
}


void endGame(){
	int scoreN,scoreB,i;
	for (i=0;i<NBCASES;i++){
		if (othellier[i/TAILLE][i%TAILLE]=='N')
			scoreN++;
		else if(othellier[i/TAILLE][i%TAILLE]=='B')
			scoreB++;
	}
	printGameWithHelp(cree_vide());
	
	if (scoreN>scoreB)
		printf("Les Noirs ont gagnés, BRAVO!!!!");
	else if (scoreN<scoreB)
		printf("Les Blancs ont gagnés, BRAVO!!!");
	else printf ("Égalité...");
	printf("\n");
}
