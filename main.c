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
char othellier_test[TAILLE][TAILLE];

void playingIA();
int minimax_ia (int depth,int maxdepth,char othellier[TAILLE][TAILLE]);
int minimax_adv (int depth,int maxdepth,char othellier[TAILLE][TAILLE]);
int score(char Player_color,char othellier[TAILLE][TAILLE]);

int main(){
	int choix=-1;
	initialization(); 
	while (choix != 0){
		printf("Choix du type de jeux:\n- 1 VS 1  (1)\n- 1 VS IA  (2)\n- IA VS IA  (3)\n - Quitter  (0)");
		scanf(" %d",&choix);
		fflush(stdin);
		if (choix!=0){		
			switch(choix){
				case 1 :	
					playing();
					break;
				case 2 :
					playingIA();
					break;
				case 3 :
					break;
			//		playing2IA()
			}
		endGame();
		}	
	}

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

void playingIA(){
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
	//Choix de l'ordi
			//L'ordinateur peut jouer en : '
			/*printf("L\'ordinateur peut jouer en : \n");
			int e;
			while(!est_vide(choix_possibles)){
				e = tete_liste(choix_possibles);
				printf("  -  %d : [%d][%d]\n",e, e/8,e%8);
				choix_possibles = queue_liste(choix_possibles);
			}*/
			printf("l\'ordi joue : \n");
		printf("	Possibilités : \n");
			
			choix=minimax_ia(2,2,othellier);		

			change_othellier(choix,'B',othellier);
			count++;
		}else{
			printf("L'ordinateur ne peux pas jouer!\n");
			playerBok = 0;
		}
	}


}
int minimax_adv(int depth,int maxdepth,char othellier[TAILLE][TAILLE]){

	int i;


	if (depth == 0)
		return score('N',othellier);
    
	int bestScore;
  	int move;
	tpl coups_jouable;

	bestScore = +1000;
	coups_jouable=coup_jouable('N',othellier);

	while(coups_jouable!=0){

		char nothellier[TAILLE][TAILLE];
		for(i=0; i<NBCASES; i++){
			nothellier[i/TAILLE][i%TAILLE] = othellier[i/TAILLE][i%TAILLE];
		}
		move=tete_liste(coups_jouable);

		coups_jouable = queue_liste(coups_jouable);
		//nouveau othellier 
		change_othellier(move,'N',nothellier);
		
		int score = minimax_ia (depth - 1,maxdepth,nothellier);

		//free othellier
		if (score < bestScore) {
				bestScore = score;
				//bestMove = move ;
		}
	}
	return bestScore ;	
}
int minimax_ia (int depth,int maxdepth,char othellier[TAILLE][TAILLE])
{
	int i;


	if (depth == 0)
		return score('B',othellier);
    
	int bestScore;
	int bestMove;
  	int move;
	tpl coups_jouable;

	bestScore = -1000;
	coups_jouable=coup_jouable('B',othellier);
		
	while(!est_vide(coups_jouable)){
		//new othellier (copy)
		char nothellier[TAILLE][TAILLE];
		for(i=0; i<NBCASES; i++){
			nothellier[i/TAILLE][i%TAILLE] = othellier[i/TAILLE][i%TAILLE];
		}
		//move on that 
		move=tete_liste(coups_jouable);
		coups_jouable = queue_liste(coups_jouable);
		//nouveau othellier
		change_othellier(move,'B',nothellier);
		int score = minimax_adv(depth - 1,maxdepth,nothellier);

		//free othellier
		if (score > bestScore) {
			bestScore = score;
			bestMove = move ;
		}
	}

   	if (depth==maxdepth)
		return bestMove;
   	
	return bestScore ;
}

int score(char Player_color,char othellier[TAILLE][TAILLE]){
	int score=0,i;
	for (i=0;i<NBCASES;i++){
		if (othellier[i/TAILLE][i%TAILLE]==Player_color)
			score++;
	}
	return score;
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
