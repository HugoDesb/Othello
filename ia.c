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
#include "calcul.h"
#include <stdlib.h>
#include "interface.h"


#define TAILLE 8
#define NBCASES 64

int minimax_ia (int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff);
int minimax_adv (int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff);
int score(char Player_color,char othellier[TAILLE][TAILLE], int diff);

int coeff_othellier[TAILLE][TAILLE] = {{ 500,-150,30,10,10,30,-150, 500},
                                       {-150,-250, 0, 0, 0, 0,-250,-150},
                                       {  30,   0, 1, 2, 2, 1,   0,  30},
                                       {  10,   0, 2,16,16, 2,   0,  10},
                                       {  10,   0, 2,16,16, 2,   0,  10},
                                       {  30,   0, 1, 2, 2, 1,   0,  30},
                                       {-150,-250, 0, 0, 0, 0,-250,-150},
                                       { 500,-150,30,10,10,30,-150, 500}};

int minimax_adv(int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff){
	int i;
	if (depth == 0)
		return score('N',othellier,diff);
    
	int bestScore;
  	int move;
	tpl coups_jouable;

	bestScore = +10000;
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
		
		int score = minimax_ia (depth - 1,maxdepth,nothellier,diff);

		//free othellier
		if (score < bestScore) {
				bestScore = score;
				//bestMove = move ;
		}
	}
	return bestScore ;	
}
int minimax_ia (int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff)
{
	int i;
	if (depth == 0)
		return score('B',othellier, diff);
    
	int bestScore;
	int bestMove;
  	int move;
	tpl coups_jouable;

	bestScore = -10000;
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
		int score = minimax_adv(depth - 1,maxdepth,nothellier,diff);
    //if (depth==maxdepth){printf("%d:%d\n",score,bestScore);printf("mm : %d,%d\n",move/TAILLE,move%TAILLE);}
		//free othellier
		if (score > bestScore) {
			bestScore = score;
			bestMove = move ;
		}
	}

   	if (depth==maxdepth){
       printf("SCOOOOOOOOORE : %d\n",bestScore);
       printf("MOOOOOOOOOVE : %d,%d\n",bestMove/TAILLE,bestMove%TAILLE);
        return bestMove;
    }  

   	
	return bestScore ;
}

int score(char Player_color,char othellier[TAILLE][TAILLE], int diff){
	int score=0,i;
  
	for (i=0;i<NBCASES;i++){
		if (othellier[i/TAILLE][i%TAILLE]==Player_color){
      if(diff==3){
        score+=coeff_othellier[i/TAILLE][i%TAILLE];
      }else{
        score++;
      }		
	  }
  }


  //////------------------affiche othellier------------------------------------------------------
  #define NORMALCOLOR  "\x1B[0m"
#define REDCOLOR  "\x1B[31m"
#define YELLOWCOLOR  "\x1B[33m"
#define BLUECOLOR  "\x1B[34m"

  printf("Score : %d\n",score);
	//Affichage des num en haut
	for(i=0; i<TAILLE;i++){
		printf(" %c ",i+65);
	}
	
	for(i=0; i<NBCASES;i++){
		if(i%(TAILLE) == 0){
			if (i!=0){
				printf("%d",i/(TAILLE)-1);
			}
			printf("\n");		
		}

		
		//Affichage en couleur d'un blanc(bleu) ou noir(rouge)
		if(othellier[i/TAILLE][i%TAILLE]=='N'){
			printf(" %sN%s ",BLUECOLOR,NORMALCOLOR);
		}else if(othellier[i/TAILLE][i%TAILLE]=='B'){
			printf(" %sB%s ",REDCOLOR,NORMALCOLOR);			
		}else{
				printf(" V ");
		}
	}
	printf("%d\n",TAILLE-1);


  return score;
}
