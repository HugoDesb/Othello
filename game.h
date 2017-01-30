#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "liste.h"
#include "interface.h"
#include "calcul.h"
#include <stdlib.h>


#define TAILLE 8
#define NBCASES 64

void initialization();
void jeu();
void playing();
void playingIA(int difficulte);
void playing2IA(int difficulteIA1, int difficulteIA2);
void endGame();