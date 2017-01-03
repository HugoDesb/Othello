/**
 * -------------------------------------------------------------------
 * Nom du fichier : liste.h
 * @author  DESBIOLLES Hugo hugo.desbiolles@etu.univ-amu.fr, VILLA Gabriel gabriel.villa@etu.univ-amu.fr
 * Objet : entete du module implantant une liste chainée d'entiers
 * --------------------------------------------------------------------
*/


#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
/*  these are the include guards */

typedef struct list{
	int val;
	struct list *  next;
} t_list, * tpl;

/* Prototypes for the functions */


/**
 * Renvoie le pointeur vide
 */
tpl cree_vide(void);

/**
 * T si la liste est égale au pointeur null, F autrement
 */
int est_vide(tpl l);

/**
 * Ajoute la valeur au début de la liste, renvoie la nouvelle liste
 */
tpl ajout_liste(int val, tpl l);

/**
 * Renvoie la première valeur de la liste
 */
int tete_liste(tpl l);

/**
 * Renvoie le ptr vers l'élément suivant de la liste
 */
tpl queue_liste(tpl l);

/**
 * Fonction qui créé et rempli une liste selon les entrées
 * de l'utilisateur.
 * Un nombre négatif termine les entrées
 */
tpl creation_liste(tpl l);

/**
 * Fonction qui affiche l'ensemble de la liste
 */
void afficher(tpl l);

/**
 * Fonction qui est utilisée par afficher(tpl l). NE PAS APPELER
 */
void afficher_liste(tpl l);

/**
 * Retourne la longueur de la liste
 */
int length(tpl l);

/**
 * Copie une liste en respectant l'ordre
 */
tpl copie(tpl l);

/**
 * Recherche et renvoie l'adresse de l'élément de la liste dont la
 * valeur est égale a X
 * Si aucun élément trouvé, renvoie le pointeur NULL
 */
tpl searchFor(int x, tpl l);

/**
 * Recherche et supprime la 1ère occurrence de l'élément de la liste
 * dont la valeur est égale a X
 * Renvoie la liste moins cet élément
 */
tpl deleteFirst(int x, tpl l);

/**
 * Recherche et supprime toutes les occurrences de l'élément de la liste
 * dont la valeur est égale a X
 * Renvoie la liste moins ces éléments
 */
tpl deleteAll(int x, tpl l);

/**
 * Effectue une copie de la liste donnée en inversant l'ordre des valeurs
 * de cette dernière
 */
tpl copieInverse(tpl l);

#endif
