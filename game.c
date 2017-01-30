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

/**
 * Fonction qui initialise l'othellier a son état de départ
 */
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

/**
 *  Fonction principale qui gère les variables de jeu de départ et la fin du jeu
 */
void jeu(){
    int choixJeu=-1;
	int choixIA1 = 0;
	int choixIA2 = 0;
	while (choixJeu != 0){
		// choix des profils joueurs
		choixJeu = askGameType();
		if (choixJeu!=0){	
			initialization();	
			switch(choixJeu){
				case 1 :	//Humain vs Humain
					playing();
					break;
				case 2 :	//Humain(Noir) vs IA(Blanc)
					printf("Choisissez la difficulté pour les Blancs\n");
                    choixIA1 = askIADifficulty();
					playingIA(choixIA1);
					break;
				case 3 :	//IA(Noir) vs IA(Blanc)
					printf("Choisissez la difficulté pour les Noirs\n");
					choixIA1 = askIADifficulty();
					printf("Choisissez la difficulté pour les Blancs\n");
					choixIA2 = askIADifficulty();
					playing2IA(choixIA1,choixIA2);
					break;
			}
		endGame();
		}	
	}
}

/**
 * Fonction qui gère le déroulement du jeu pour 2 humains
 */
void playing(){
	int playerNok = 1,playerBok = 1;
	int choix,count = 4;
	tpl choix_possibles;

	//Boucle de jeu (conditions de fin de jeu)
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

/**
 * Fonction qui gère le déroulement du jeu pour 1 humains (Noir) et 1 IA (Blanc)
 */
void playingIA(int difficulte){
	int playerNok = 1,playerBok = 1,profondeur;
	int choix,count = 4;
	tpl choix_possibles;

	//Définition des paramètres de l'IA Blanc
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

	//Boucle de jeu (conditions de fin de jeu)
	while((playerNok || playerBok) && count<64){
		playerNok = 1;
		playerBok = 1;
		
			//Joueur Noir
		choix_possibles = coup_jouable('N',othellier);
		if(!est_vide(choix_possibles)){
			printf("Les noirs jouent.\n");
			printGameWithHelp(choix_possibles);
			//choix humain
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
			//choix IA
			choix=minimax_ia(profondeur,profondeur,othellier, difficulte,'B');		
			change_othellier(choix,'B',othellier);
			count++;
		}else{
			printf("L'ordinateur ne peux pas jouer!\n");
			playerBok = 0;
		}
	}
}

/**
 * Fonction qui gère le déroulement du jeu pour 2 IA
 */
void playing2IA(int difficulteIA1, int difficulteIA2){
	int playerNok = 1,playerBok = 1,profondeurIA1 ,profondeurIA2 ,choix ,count=4;
	tpl choix_possibles;

	//Définition des paramètres des IA
	//Noir
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
	//Blanc
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

	//Boucle de jeu (conditions de fin de jeu)
	while((playerNok || playerBok) && count<64){
		playerNok = 1;
		playerBok = 1;
		
			//Joueur Noir
		choix_possibles = coup_jouable('N',othellier);
		if(!est_vide(choix_possibles)){
			printf("Les noirs jouent.\n");
			printGameWithHelp(choix_possibles);
			choix=minimax_ia(profondeurIA1,profondeurIA1,othellier, difficulteIA1,'N');
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
			choix=minimax_ia(profondeurIA2,profondeurIA2,othellier, difficulteIA2,'B');		
			change_othellier(choix,'B',othellier);
			count++;
		}else{
			printf("L'IA Blanc ne peux pas jouer!\n");
			playerBok = 0;
		}
	}
}

/**
 * Fonction qui affiche les scores et le gagnant
 */
void endGame(){
	int scoreN,scoreB,i;
	//calcul des scores
	for (i=0;i<NBCASES;i++){
		if (othellier[i/TAILLE][i%TAILLE]=='N')
			scoreN++;
		else if(othellier[i/TAILLE][i%TAILLE]=='B')
			scoreB++;
	}
	//affiche l'othellier en fin de partie
	printGameWithHelp(cree_vide()); 
	
	//Affichage des scores
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
