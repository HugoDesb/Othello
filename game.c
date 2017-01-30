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
#include "ia.h"


#define TAILLE 8
#define NBCASES 64

void initialization();
void jeu();
void playing();
void playingIA(int difficulte);
void playing2IA(int difficulteIA1, int difficulteIA2);
void endGame();


extern char othellier[TAILLE][TAILLE] ;

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

void jeu(){
    int choixJeu=-1;
	int choixIA1 = 0;
	int choixIA2 = 0;
	while (choixJeu != 0){
		choixJeu = askGameType();
		if (choixJeu!=0){		
			switch(choixJeu){
				case 1 :	
					playing();
					break;
				case 2 :
                    choixIA1 = askIADifficulty();
					playingIA(choixIA1);
					break;
				case 3 :
					choixIA1 = askIADifficulty();
					choixIA2 = askIADifficulty();
					playing2IA(choixIA1,choixIA2);
					break;
			}
		endGame();
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
		choix_possibles = coup_jouable('N',othellier);
		if(!est_vide(choix_possibles)){
			printf("Les noirs jouent.\n");
			printGameWithHelp(choix_possibles);
			choix = askPlayer(choix_possibles);
			change_othellier(choix,'N',othellier);
			count++;
		}else{
			printf("Désolé, tu ne peux pas jouer!\n");
			playerNok = 0;
		}
	
			//Joueur Blanc
		choix_possibles = coup_jouable('B',othellier);
		if(!est_vide(choix_possibles)){
			printf("Les blancs jouent.\n");
			printGameWithHelp(choix_possibles);
			choix = askPlayer(choix_possibles);
			change_othellier(choix,'B',othellier);
			count++;
		}else{
			printf("Désolé, tu ne peux pas jouer!\n");
			playerBok = 0;
		}
	}
}
void playingIA(int difficulte){
	int playerNok = 1,playerBok = 1;
	int choix,count = 4;
	tpl choix_possibles;
	
	while((playerNok || playerBok) && count<64){
		playerNok = 1;
		playerBok = 1;
		
			//Joueur Noir
		choix_possibles = coup_jouable('N',othellier);
		if(!est_vide(choix_possibles)){
			printf("Les noirs jouent.\n");
			printGameWithHelp(choix_possibles);
			choix = askPlayer(choix_possibles);
			change_othellier(choix,'N',othellier);
			count++;
		}else{
			printf("Désolé, tu ne peux pas jouer!\n");
			playerNok = 0;
		}
	
			//Joueur Blanc
		choix_possibles = coup_jouable('B',othellier);
		if(!est_vide(choix_possibles)){
			printf("Les blancs jouent.\n");
			//---------------------------------------------------------------------------------------------
            int profondeur;
            switch(difficulte){
                case 1:
                    profondeur = 2;
                    break;
                case 2: 
                    profondeur = 2;
                    break;
                case 3 : 
                    profondeur = 4;
                    break;
            }

            printGameWithHelp(choix_possibles);
			choix=minimax_ia(profondeur,profondeur,othellier, difficulte);		

			change_othellier(choix,'B',othellier);
			count++;
		}else{
			printf("L'ordinateur ne peux pas jouer!\n");
			playerBok = 0;
		}
	}
}

void playing2IA(int difficulteIA1, int difficulteIA2){
	int playerNok = 1,playerBok = 1,profondeurIA1 ,profondeurIA2 ,choix ,count=4;
	tpl choix_possibles;

	//Définition des paramètres des IA
	switch(difficulteIA1){
		case 1:
			profondeurIA1 = 2;
			break;
		case 2: 
			profondeurIA1 = 2;
			break;
		case 3 : 
			profondeurIA1 = 4;
			break;
	}
	switch(difficulteIA2){
		case 1:
			profondeurIA2 = 2;
			break;
		case 2: 
			profondeurIA2 = 2;
			break;
		case 3 : 
			profondeurIA2 = 4;
			break;
	}

	
	while((playerNok || playerBok) && count<64){
		playerNok = 1;
		playerBok = 1;
		
			//Joueur Noir
		choix_possibles = coup_jouable('N',othellier);
		if(!est_vide(choix_possibles)){
			printf("Les noirs jouent.\n");
			printGameWithHelp(choix_possibles);
			choix=minimax_ia(profondeurIA1,profondeurIA1,othellier, difficulteIA1);
			change_othellier(choix,'N',othellier);
			count++;
		}else{
			printf("L'IA Noir ne peux pas jouer!\n");
			playerNok = 0;
		}
	
			//Joueur Blanc
		choix_possibles = coup_jouable('B',othellier);
		if(!est_vide(choix_possibles)){
			printf("Les blancs jouent.\n");
			printGameWithHelp(choix_possibles);
			choix=minimax_ia(profondeurIA2,profondeurIA2,othellier, difficulteIA2);		
			change_othellier(choix,'B',othellier);
			count++;
		}else{
			printf("L'IA Blanc ne peux pas jouer!\n");
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
	
	if (scoreN>scoreB){
		printf("Les Noirs ont gagnés, BRAVO!!!!\n");
        printf("%d à %d", scoreN, scoreB);
    }
	else if (scoreN<scoreB){
		printf("Les Blancs ont gagnés, BRAVO!!!\n");
        printf("%d à %d", scoreB, scoreN);
    }
	else {
        printf ("Égalité...\n");
        printf("%d à %d", scoreB, scoreN);
    }
	printf("\nNouvelle Partie ! \n");
}
