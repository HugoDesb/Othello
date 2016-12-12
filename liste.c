/** 
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

/**
 * @author DESBIOLLES Hugo hugo.desbiolles@etu.univ-amu.fr>
 */


/**
 * @file liste.c
 * 
 *  LISTES CHAINEES
 */

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "liste.h"


tpl cree_vide(void);
int est_vide(tpl l);
tpl ajout_liste(int val, tpl l);
int tete_liste(tpl l);
tpl queue_liste(tpl l);
tpl creation_liste(tpl l);
tpl creation_liste_ptr(tpl l);
void afficher(tpl l);
void afficher_liste(tpl l);
int length(tpl l);
int lengthWhile(tpl l);
int length_ptr(tpl l);
int lengthWhile_ptr(tpl l);
tpl copie(tpl l);
tpl searchFor(int x, tpl l);
tpl copie_ptr(tpl l);
tpl searchFor_ptr(int x, tpl l);
tpl deleteFirst(int x, tpl l);
tpl deleteAll(int x, tpl l);
tpl copieInverse(tpl l);
tpl copieInverse_ptr(tpl l);


/**
 * Fonction qui affiche l'ensemble de la liste
 */
void afficher(tpl l){
	printf("(");
	afficher_liste(l);
	printf(")\n");
}
/**
 * Fonction qui est utilisée par afficher(tpl l). NE PAS APPELER
 */
void afficher_liste(tpl l){
	if(est_vide(queue_liste(l))){
		printf("%d",tete_liste(l));
	}else{
		printf("%d,",tete_liste(l));
		afficher_liste(queue_liste(l));
	}
}
/**
 * Fonction qui créé et rempli une liste selon les entrées
 * de l'utilisateur.
 * Un nombre négatif termine les entrées
 */
tpl creation_liste(tpl l){
	int val;
	do{
		printf("Entrez une valeur : ");
		scanf("%d",&val);
		if(val>=0){
			l = ajout_liste(val, l);
		}
	}while(val>=0);
	return l;
}
/**
 * Renvoie le pointeur vide
 */
tpl cree_vide(void){
	return (tpl)NULL;
}
/**
 * T si la liste est égale au pointeur null, F autrement
 */
int est_vide(tpl l){
	return l==cree_vide();
}
/**
 * Ajoute la valeur au début de la liste, renvoie la nouvelle liste
 */
tpl ajout_liste(int val, tpl l){
	tpl newL;
	newL = (tpl)malloc(sizeof(t_list));
	newL->val = val;
	newL->next = l;
	return newL;
}
/**
 * Renvoie la première valeur de la liste
 */
int tete_liste(tpl l){
	assert(l);
	return l->val;
}
/**
 * Renvoie le ptr vers l'élément suivant de la liste
 */
tpl queue_liste(tpl l){
	assert(l);
	return l->next;
}
/**
 * Retourne la longueur de la liste
 */
int length(tpl l){
	if(est_vide(l)){
		return 0;
	}else{
		return 1+length(queue_liste(l));
	}
}

/**
 * Copie une liste en respectant l'ordre
 */
tpl copie(tpl l){
	if(est_vide(l)){
		return cree_vide();
	}else{
		return ajout_liste(tete_liste(l), copie(queue_liste(l)));
	}
}
/**
 * Recherche et renvoie l'adresse de l'élément de la liste dont la
 * valeur est égale a X
 * Si aucun élément trouvé, renvoie le pointeur NULL
 */
tpl searchFor(int x, tpl l){
	if(est_vide(l)){
		return cree_vide();
	}else{
		if(tete_liste(l)==x){
			return l;
		}else{
			return searchFor(x, queue_liste(l));
		}
	}
}
/**
 * Recherche et supprime la 1ère occurrence de l'élément de la liste
 * dont la valeur est égale a X
 * Renvoie la liste moins cet élément
 */
tpl deleteFirst(int x , tpl l){
	tpl curr = l;
	tpl suiv = l->next;
	tpl ret = l;
	int found = 0;
	
	if(l->val != x){
		while(suiv!=(tpl)NULL && !found){
			if(suiv->val == x){
				curr->next = suiv->next;
				free(suiv);
				found = 1;
			}else{
				curr = suiv;
				suiv = suiv->next;
			}
		}
	}else{
		//Cas où l'élément a supprimer est le 1er
		ret = l->next;
		free(l);
	}
	return ret;
}
/**
 * Recherche et supprime toutes les occurrences de l'élément de la liste
 * dont la valeur est égale a X
 * Renvoie la liste moins ces éléments
 */
tpl deleteAll(int x , tpl l){
	tpl curr = l;
	tpl suiv = l->next;
	tpl ret = l;

	
	if(l->val != x){
		while(suiv!=(tpl)NULL){
			if(suiv->val == x){
				curr->next = suiv->next;
				free(suiv);
			}else{
				curr = suiv;
				suiv = suiv->next;
			}
		}
	}else{
		//Cas où l'élément a supprimer est le 1er
		ret = deleteAll(x,l->next);
		free(l);
	}
	return ret;
}
/**
 * Effectue une copie de la liste donnée en inversant l'ordre des valeurs
 * de cette dernière
 */
tpl copieInverse(tpl l){
	tpl copie = cree_vide();
	tpl curr = l;
	while(!est_vide(curr)){
		copie = ajout_liste(tete_liste(curr), copie);
		curr = queue_liste(curr);
	}
	return copie;
}

