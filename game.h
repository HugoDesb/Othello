#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "liste.h"
#include "interface.h"
#include "calcul.h"
#include <stdlib.h>


#define TAILLE 8
#define NBCASES 64

/**
 * Fonction qui initialise l'othellier a son état de départ
 */
void initialization();

/**
 *  Fonction principale qui gère les variables de jeu de départ et la fin du jeu
 */
void jeu();

/**
 * Fonction qui gère le déroulement du jeu pour 2 humains
 */
void playing();

/**
 * Fonction qui gère le déroulement du jeu pour 1 humains (Noir) et 1 IA (Blanc)
 */
void playingIA(int difficulte);

/**
 * Fonction qui gère le déroulement du jeu pour 2 IA
 */
void playing2IA(int difficulteIA1, int difficulteIA2);

/**
 * Fonction qui affiche les scores et le gagnant
 */
void endGame();