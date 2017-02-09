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

int minimax_ia (int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff,char player);
int minimax_adv (int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff,char player);
int score(char Player_color,char othellier[TAILLE][TAILLE], int diff);

int coeff_othellier[TAILLE][TAILLE] = {{ 500,-150,30,10,10,30,-150, 500},
                                       {-150,-250, 0, 0, 0, 0,-250,-150},
                                       {  30,   0, 1, 2, 2, 1,   0,  30},
                                       {  10,   0, 2,16,16, 2,   0,  10},
                                       {  10,   0, 2,16,16, 2,   0,  10},
                                       {  30,   0, 1, 2, 2, 1,   0,  30},
                                       {-150,-250, 0, 0, 0, 0,-250,-150},
                                       { 500,-150,30,10,10,30,-150, 500}};

/**
 * Fonction MiniMax qui renvoie le meilleur coup a jouer (si depth = 0 ) ou le meilleur score 
 * Appelle la récusrion avec minimax_ia
 * depth DOIT être impair
 */
int minimax_adv(int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff,char player){
	int i , bestScore , move,nscore;
	char opponent;
	char copie_othellier[TAILLE][TAILLE];
	tpl coups_jouable;

	//Condition d'arrêt de la récursion
	if (depth == 0)
		return score(player,othellier,diff);
    
	// Le bestScore est min (donc initialisation au maximum)
	bestScore = +10000;
	coups_jouable=coup_jouable(player,othellier);

	//Parcours de tous les coups possibles 
	while(coups_jouable!=0){
		//On fait une copie de l'othellier 
		//(pour ne pas modifier l'état a partir duquel on explore)
		for(i=0; i<NBCASES; i++){
			copie_othellier[i/TAILLE][i%TAILLE] = othellier[i/TAILLE][i%TAILLE];
		}
		// Choix d'un coup
		move=tete_liste(coups_jouable);
		// pour la suite de la boucle 
		coups_jouable = queue_liste(coups_jouable);
		//nouveau othellier avec le coup choisi
		change_othellier(move,player,copie_othellier);

		//calcul du best score en utilisant la récusrion
		// coté adversaire
		opponent = getOpponent(player);
		nscore = minimax_ia (depth - 1,maxdepth,copie_othellier,diff,opponent);

		//Pour le minmax de l'adversaire, on récupère le score min 
		if (nscore < bestScore) {
			bestScore = nscore;
		}
	}
	//Dans le cadre de la récursion, on renvoie le score minimum
	return bestScore ;	
}

/**
 * Fonction MiniMax qui renvoie le meilleur coup a jouer (si depth = 0 ) ou le meilleur score 
 * Appelle la récusrion avec minimax_adv
 * Entrée de la fonction (fonction initiale)
 * depth DOIT être pair
 */
int minimax_ia (int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff,char player)
{
	int i , bestScore , bestMove , move,nscore ;
	char opponent;
	char copie_othellier[TAILLE][TAILLE];
	tpl coups_jouable;

	//Condition d'arrêt de la récursion
	if (depth == 0)
		return score(player,othellier, diff);
    
	
	// Le bestScore est max (donc initialisation au minimum)
	bestScore = -10000;
	coups_jouable=coup_jouable(player,othellier);
		
	//Parcours de tous les coups possibles 
	while(!est_vide(coups_jouable)){
		//On fait une copie de l'othellier 
		//(pour ne pas modifier l'état a partir duquel on explore)
		for(i=0; i<NBCASES; i++){
			copie_othellier[i/TAILLE][i%TAILLE] = othellier[i/TAILLE][i%TAILLE];
		}

		// Choix d'un coup
		move=tete_liste(coups_jouable);
		// pour la suite de la boucle 
		coups_jouable = queue_liste(coups_jouable);
		//nouveau othellier avec le coup choisi
		change_othellier(move,player,copie_othellier);

		//calcul du best score en utilisant la récusrion
		// coté adversaire
		opponent = getOpponent(player);
		nscore = minimax_adv(depth - 1,maxdepth,copie_othellier,diff,opponent );
		//Pour le minmax du joueur, on récupère le score max 
		// avec son coup associé
		if (nscore >= bestScore) {
			bestScore = nscore;
			bestMove = move ;
		}
	}

	//On retourne le coup choisi
   	if (depth==maxdepth){
		printf("Le joueur %c joue en %c%d \n\n",player,bestMove%TAILLE+65,bestMove/TAILLE);
        return bestMove;
    }  

   	//Dans le cadre de la récursion, on renvoie le score maximum
	return bestScore ;
}

/**
 * Calcul du score pour la couleur donnée et la difficulté 
 * (si = 2 ou 3, prise en compte des coefficients)
 */
int score(char Player_color,char othellier[TAILLE][TAILLE], int diff){
	int nscore=0,i;
  
	for (i=0;i<NBCASES;i++){
		if (othellier[i/TAILLE][i%TAILLE]==Player_color){
			if(diff==3 || diff == 2){
				nscore+=coeff_othellier[i/TAILLE][i%TAILLE];
  	    	}else{
  	    		nscore++;
			}		
		}
	}
  return nscore;
}
