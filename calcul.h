/**
 * -------------------------------------------------------------------
 * Nom du fichier : calcul.h
 * @author  DESBIOLLES Hugo hugo.desbiolles@etu.univ-amu.fr, VILLA Gabriel gabriel.villa@etu.univ-amu.fr
 * Objet : entete du module définissant les fonctions servant à faire les calculs
 * --------------------------------------------------------------------
*/

#include "liste.h"

#define TAILLE 8

//Prototypes des fonctions

/**
 * Renvoie une liste chainée contenant les coordonnées des points dont la couleur
 * est désigné par le paramètre playerColor.
 */
tpl cases_occupes(char playerColor,char othellier[TAILLE][TAILLE]);

/**
 * Explore dans toutes les directions s'il existe des cases où il est possible de jouer
 * Ajoute ces cases dans la liste tpl
 * Renvoie le nouvelle liste
 */
tpl possibleForThisPoint(int point, char playerColor, tpl liste,char othellier[TAILLE][TAILLE]);

/**
 * Renvoie un point de l'othellier si, en partant du point donné,
 * et en suivant une direction précise donnée, un coup est jouable
 *
 * Si un coup est jouable, la coordonné au format (int) est renvoyée,
 * Sinon, -1 est renvoyé,
 *
 * Ici, les données fournies sont supposées valides ! Aucun contrôle n'est effectué
 * préalablement (par exemple que la case de départ est bien de la couleur du joueur)
 */
int findIfPossibleInDirection(int point, int Dx, int Dy,char playerColor,char othellier[TAILLE][TAILLE]);	

/**
 * Ajoute à la liste des coups possibles si un coup possible est trouvé
 * Sinon, ignoré.
 */
tpl addIfPossibleInDirection(int point, int Dx, int Dy,char playerColor, tpl liste,char othellier[TAILLE][TAILLE]);

/**
 * Renvoie la liste chainée de tous les coups jouables pour la couleur donnée par le paramètre playerColor
 */
tpl coup_jouable(char playerColor,char othellier[TAILLE][TAILLE]);

/**
 * A partir d'une case, teste dans les huit directions si ce coup change la couleur d'autres cases grace à la fonction changeColorInDirection
 */
void change_othellier(int point,char playerColor,char othellier[TAILLE][TAILLE]);
/**
 * Cherche si un pion est utilisable pour retourner les pions jusq'au point d'origine
 * En suivant la direction donnée.
 */ 
void changeColorInDirection(int point,int Dx, int Dy,char playerColor,char othellier[TAILLE][TAILLE]);

/**
 * Fonction qui recalcule les nouvelles coordonnées d'un point
 * selon un décalage donnée par un vecteur
 */
void computeNextPoint(int * pointX, int * pointY, int Dx, int Dy);

/**
 * Retourne la couleur de l'adversaire !! il faut envoyer 'N' ou 'B' !!
 */
 char getOpponent(char c);


