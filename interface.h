/**
 * -------------------------------------------------------------------
 * Nom du fichier : interface.h
 * @author  DESBIOLLES Hugo hugo.desbiolles@etu.univ-amu.fr, VILLA Gabriel gabriel.villa@etu.univ-amu.fr
 * Objet : entete du module définissant les fonctions servant à l'interface
 * --------------------------------------------------------------------
*/

#include "liste.h"


//Prototypes des fonctions

/**
 * Affiche l'othellier tel qu'il est
 */
void printGame();

/**
 * Fonction qui affiche l'othellier avec les coups possibles
 * pour la couleur qui joue
 */
void printGameWithHelp(tpl l);

/**
 * Demande au joueur la case ou celui-ci veut jouer et teste si le joueur a le droit de jouer à cet endroit
 */
int askPlayer(tpl l);	

/** 
 * Gère la syntaxe de l'entrée donnée par le joueur
 */
int humanInput();

/**
 * Demande le type de jeu (doit etre 1,2 ou 3)
 */
 int askGameType();

 /**
 * Demande la difficulé de l'IA (doit etre 1,2 ou 3)
 */
 int askIADifficulty();