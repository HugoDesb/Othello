#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "liste.h"
#include "calcul.h"
#include <stdlib.h>


#define TAILLE 8
#define NBCASES 64

int minimax_ia (int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff);
int minimax_adv (int depth,int maxdepth,char othellier[TAILLE][TAILLE], int diff);
int score(char Player_color,char othellier[TAILLE][TAILLE], int diff);