/**
 * -------------------------------------------------------------------
 * Nom du fichier : calcul.c
 * @author  DESBIOLLES Hugo hugo.desbiolles@etu.univ-amu.fr, VILLA Gabriel gabriel.villa@etu.univ-amu.fr
 * Objet : Fonctions de calculs 
 * --------------------------------------------------------------------
*/


#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "calcul.h"
#include "liste.h"

#define TAILLE 8
#define NBCASES 64
extern char othellier[TAILLE][TAILLE] ;
/**
 * Renvoie une liste chainée contenant les coordonnées des points dont la couleur
 * est désigné par le paramètre playerColor.
 */

tpl cases_occupes(char playerColor,char othellier[TAILLE][TAILLE]){	
	tpl spots = cree_vide();
	int i;
	for(i=0; i<NBCASES;i++){
		if(othellier[i/TAILLE][i%TAILLE]==playerColor){
			spots = ajout_liste(i,spots);
		}
	}
	return spots;
}



/**
 * Explore dans toutes les directions s'il existe des cases où il est possible de jouer
 * Ajoute ces cases dans la liste tpl
 * Renvoie le nouvelle liste
 */
tpl possibleForThisPoint(int point, char playerColor, tpl liste, char othellier[TAILLE][TAILLE]){
	liste = addIfPossibleInDirection(point, -1, -1 ,playerColor, liste,othellier);
	liste = addIfPossibleInDirection(point, -1,  0 ,playerColor, liste,othellier);
	liste = addIfPossibleInDirection(point, -1,  1 ,playerColor, liste,othellier);
	liste = addIfPossibleInDirection(point,  0, -1 ,playerColor, liste,othellier);
	liste = addIfPossibleInDirection(point,  0,  1 ,playerColor, liste,othellier);
	liste = addIfPossibleInDirection(point,  1, -1 ,playerColor, liste,othellier);
	liste = addIfPossibleInDirection(point,  1,  0 ,playerColor, liste,othellier);
	liste = addIfPossibleInDirection(point,  1,  1 ,playerColor, liste,othellier);
	return liste;
}



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
int findIfPossibleInDirection(int point, int Dx, int Dy,char playerColor,char othellier[TAILLE][TAILLE]){
	int pointX = point/TAILLE,
		  pointY = point%TAILLE,
  		adversaryColorFound = 0,
		  out = 0,
		  ret = -1;

	// détermine la couleur adverse
	char adversaryColor = (playerColor == 'N') ? 'B' : 'N';

	computeNextPoint(&pointX,&pointY, Dx, Dy);
	while(!out){
		//Condition d'arrêt : Sortis de l'othellier si les noueveaux points
		//ne sont pas valides
		if( ((0>pointX) || (pointX>=TAILLE)) || ((0>pointY) || (pointY>=TAILLE))){
			out = 1;
		}else{		
			if(othellier[pointX][pointY] == playerColor){
				//case couleur joueur
				//Quel que soit le cas, il n'y a aucun intérêt a chercher :
				//   - Si il y a des B avant, alors il ne sera pas possible de jouer
				//   - Si il n'y en a pas (c-a-d 2 N de suite), alors ça concerne un autre pion
				out = 1;
			}else if(othellier[pointX][pointY] == adversaryColor){
				//case couleur adverse
				adversaryColorFound = 1;
				
				//continue
				computeNextPoint(&pointX,&pointY, Dx, Dy);
			}else{
				//case vide
				if(adversaryColorFound){
					ret = pointX*TAILLE + pointY;
					out = 1;
				}else{
					//sortir
					out = 1;		
				}
			}
		}
	}
	return ret;
} 



/**
 * Ajoute a la liste des coups possibles si un coup possible est trouvé
 * Sinon, ignoré.
 */
tpl addIfPossibleInDirection(int point, int Dx, int Dy,char playerColor, tpl liste,char othellier[TAILLE][TAILLE]){
	int result = findIfPossibleInDirection(point, Dx, Dy,playerColor,othellier);
	if(result != -1){
		liste = ajout_liste(result,liste);
	}
	return liste;
}


/**
 * Renvoie la liste chainée de tous les coups jouables pour la couleur donnée par le paramètre playerColor
 */
tpl coup_jouable(char playerColor,char othellier[TAILLE][TAILLE]){

	tpl possibleSpots = cree_vide();
	tpl occupiedSpots = cases_occupes(playerColor,othellier);

	while(!est_vide(occupiedSpots)){
		//On ajoute tous les coups possibles pour ce point là a la liste
		possibleSpots = possibleForThisPoint(tete_liste(occupiedSpots), playerColor, possibleSpots,othellier);
		
		occupiedSpots = queue_liste(occupiedSpots);
	}

	return possibleSpots;
}


/**
 * A partir d'une case, teste dans les huit directions si ce coup change la couleur d'autres cases grace à la fonction changeColorInDirection
 */
void change_othellier(int point,char playerColor,char othellier[TAILLE][TAILLE]){
	changeColorInDirection(point, -1, -1 ,playerColor,othellier);
	changeColorInDirection(point, -1,  0 ,playerColor,othellier);
	changeColorInDirection(point, -1,  1 ,playerColor,othellier);
	changeColorInDirection(point,  0, -1 ,playerColor,othellier);
	changeColorInDirection(point,  0,  1 ,playerColor,othellier);
	changeColorInDirection(point,  1, -1 ,playerColor,othellier);
	changeColorInDirection(point,  1,  0 ,playerColor,othellier);
	changeColorInDirection(point,  1,  1 ,playerColor,othellier);
}

/**
 * Cherche si un pion est utilisable pour retourner les pions jusq'au point d'origine
 * En suivant la direction donnée.
 */ 
void  changeColorInDirection(int point,int Dx, int Dy,char playerColor,char othellier[TAILLE][TAILLE]){

	int pointX = point/TAILLE,
		  pointY = point%TAILLE,
		  adversaryColorFound = 0,
		  out = 0;
	
	// détermine la couleur adverse
	char adversaryColor = (playerColor == 'N') ? 'B' : 'N';

	computeNextPoint(&pointX,&pointY, Dx, Dy);
	while(!out){
		//Condition d'arrêt : Sortis de l'othellier si les noueveaux points
		//ne sont pas valides
		if( ((0>pointX) || (pointX>=TAILLE)) || ((0>pointY) || (pointY>=TAILLE))){
			out = 1;
		}else{		
			if(othellier[pointX][pointY] == playerColor){
				//case couleur joueur
				// Alors on peut 'flip' jusque la SSI couleur adverse trouvée
				if(adversaryColorFound){
 
					//changement de l'othellier dans la direction inverse
					out = 0;
					computeNextPoint(&pointX,&pointY, -Dx, -Dy);
					while(!out){
						//le pt de départ est la 1ere case vide
						if((point/TAILLE==pointX) && (point%TAILLE==pointY)){
							out = 1;
						}
						othellier[pointX][pointY] = playerColor;
						computeNextPoint(&pointX,&pointY, -Dx, -Dy);
					}
					out = 1;
				}else{
					out = 1;
				}
			}else if(othellier[pointX][pointY] == adversaryColor){
				//case couleur adverse
				adversaryColorFound = 1;
				
				//continue
				computeNextPoint(&pointX,&pointY, Dx, Dy);
			}else{
				//case vide
				// on arrête la recherche 
				out = 1;
			}
		}
	}	
}


/**
 * Fonction qui recalcule les nouvelles coordonnées d'un point
 * selon un décalage donnée par un vecteur
 */
void computeNextPoint(int * pointX, int * pointY, int Dx, int Dy){
	*pointX = *pointX + Dx;
	*pointY = *pointY + Dy;
}
