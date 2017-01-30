#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "liste.h"
#include "calcul.h"
#include <stdlib.h>


#define TAILLE 8
#define NBCASES 64


/**
 * Fonction MiniMax qui renvoie le meilleur coup a jouer (si depth = 0 ) ou le meilleur score 
 * Appelle la récusrion avec minimax_adv
 * Entrée de la fonction (fonction initiale)
 * depth DOIT être pair
 */
int minimax_ia (int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff,char player);

/**
 * Fonction MiniMax qui renvoie le meilleur coup a jouer (si depth = 0 ) ou le meilleur score 
 * Appelle la récusrion avec minimax_ia
 * depth DOIT être impair
 */
int minimax_adv (int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff,char player);

/**
 * Calcul du score pour la couleur donnée et la difficulté 
 * (si = 2 ou 3, prise en compte des coefficients)
 */
int score(char Player_color,char othellier[TAILLE][TAILLE], int diff);