#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "liste.h"

#define TAILLE 8
#define NBCASES 64

//----------------------COLORS --------------------
#define NORMALCOLOR  "\x1B[0m"
#define REDCOLOR  "\x1B[31m"
#define YELLOWCOLOR  "\x1B[33m"
#define BLUECOLOR  "\x1B[34m"

int main();
void initialization();
void printGame();
void printGameWithHelp(char couleur);
tpl cases_occupes(char playerColor);
tpl possibleForThisPoint(int point, char playerColor, tpl liste);
int findIfPossibleInDirection(int point, int Dx, int Dy,char playerColor);
tpl addIfPossibleInDirection(int point, int Dx, int Dy,char playerColor, tpl liste);
tpl coup_jouable(char playerColor);
void change_othellier(int p,char c);
int humanInput();
void computeNextPoint(int * pointX, int * pointY, int Dx, int Dy);


char othellier[TAILLE][TAILLE] ;



int main(){
	initialization();
	while(1){
		printf("Les noirs jouent.\n");
		printGameWithHelp('N');
		change_othellier(humanInput(),'N');
		printf("Les blancs jouent.\n");
		printGameWithHelp('B');
		change_othellier(humanInput(),'B');
	}
	
	return 0;
}


void initialization(){		
	int i;
	for(i=0; i<NBCASES;i++){
		if(i==27 || i==36){
			othellier[i/8][i%8] = 'N';
		}else if(i==28 || i==35){
			othellier[i/8][i%8] = 'B';
		}else{
			othellier[i/8][i%8] = 'V';
		}
	}
}

void printGame(){		//Affiche l'othellier
	int i;
	//Affichage des num en haut
	for(i=0; i<TAILLE;i++){
		printf(" %c ", i+65);
	}
	
	for(i=0; i<NBCASES;i++){
		if(i%(TAILLE) == 0){
			if (i!=0){
				printf("%d",i/(TAILLE)-1);
			}
			printf("\n");		
		}
		printf(" %c ",othellier[i/TAILLE][i%TAILLE]);	
	}
	printf("%d\n",TAILLE-1);
}

/**
 * Fonction qui affiche l'othellier avec les coups possibles
 * pour la couleur passé en paramêtre
 */
void printGameWithHelp(char couleur){
	//On récupère les 
	
	tpl cases = coup_jouable(couleur);

	
	
	int i;
	//Affichage des num en haut
	for(i=0; i<TAILLE;i++){
		printf(" %c ",i+65);
	}
	
	for(i=0; i<NBCASES;i++){
		if(i%(TAILLE) == 0){
			if (i!=0){
				printf("%d",i/(TAILLE)-1);
			}
			printf("\n");		
		}

		
		//Affichage en couleur d'un blanc(bleu) ou noir(rouge)
		if(othellier[i/TAILLE][i%TAILLE]=='N'){
			printf(" %sN%s ",BLUECOLOR,NORMALCOLOR);
		}else if(othellier[i/TAILLE][i%TAILLE]=='B'){
			printf(" %sB%s ",REDCOLOR,NORMALCOLOR);			
		}else{
			//Recherche si la case vide est jouable
			tpl searchResult = searchFor(i, cases);
			if(!est_vide(searchResult)){
				printf(" %sV%s ",YELLOWCOLOR,NORMALCOLOR);
			}else{
				printf(" V ");
			}
		}
	}
	printf("%d\n",TAILLE-1);
}
/**
 * Renvoie une liste chainée contenant les coordonnées des points dont la couleur
 * est J.
 */
tpl cases_occupes(char playerColor){	
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
 * Renvoie la liste chainée de tous les coups jouables pour la couleur donnée
 */
tpl coup_jouable(char playerColor){

	tpl possibleSpots = cree_vide();
	tpl occupiedSpots = cases_occupes(playerColor);

	while(!est_vide(occupiedSpots)){
		//On ajoute tous les coups possibles pour ce point là a la liste
		possibleSpots = possibleForThisPoint(tete_liste(occupiedSpots), playerColor, possibleSpots);
		
		occupiedSpots = queue_liste(occupiedSpots);
	}
	return possibleSpots;
	
}
/**
 * Explore in all directions if there is possible spots
 * Add all of them into liste tpl.
 * Returns the new list. 
 */
tpl possibleForThisPoint(int point, char playerColor, tpl liste){
	liste = addIfPossibleInDirection(point, -1, -1 ,playerColor, liste);
	liste = addIfPossibleInDirection(point, -1,  0 ,playerColor, liste);
	liste = addIfPossibleInDirection(point, -1,  1 ,playerColor, liste);
	liste = addIfPossibleInDirection(point,  0, -1 ,playerColor, liste);
	liste = addIfPossibleInDirection(point,  0,  1 ,playerColor, liste);
	liste = addIfPossibleInDirection(point,  1, -1 ,playerColor, liste);
	liste = addIfPossibleInDirection(point,  1,  0 ,playerColor, liste);
	liste = addIfPossibleInDirection(point,  1,  1 ,playerColor, liste);
	return liste;
}
/**
 * Ajoute a la liste des coups possibles si un coup possible est trouvé
 * Sinon, ignoré.
 */
tpl addIfPossibleInDirection(int point, int Dx, int Dy,char playerColor, tpl liste){
	int result = findIfPossibleInDirection(point, Dx, Dy,playerColor);
	if(result != -1){
		liste = ajout_liste(result,liste);
	}
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
int findIfPossibleInDirection(int point, int Dx, int Dy,char playerColor){
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

void change_othellier(int p,char c){ //p est la case changee par le joueur c
	char jj=c,ja;
	int i,j,trouve,out,tmp,x,cpt;
	if (jj=='N')ja='B'; else ja='N';
	i=p/TAILLE;	//ligne de p		
	j=p%TAILLE;	//colonne de p
		
	// vers la droite
	if ((p+1)/TAILLE==i && othellier[i][j+1]==ja){
			
		trouve=0;
		out=0;
		tmp=p+2;
		while(trouve==0 && out==0){
				if (tmp/TAILLE!=i)
					out=1;
				else if (othellier[i][tmp%TAILLE]==jj){
					trouve=1;	
					}
		tmp++;	
		}
		tmp--;
		if (trouve){
			for(x=tmp;x>=p;x--){
				othellier[i][x%TAILLE]=c;		 
			}		
		}
	}
	// vers la gauche
	if ((p-1)/TAILLE==i && othellier[i][j-1]==ja){
			
		trouve=0;
		out=0;
		tmp=p-2;
		while(trouve==0 && out==0){
				if (tmp/TAILLE!=i)
					out=1;
				else if (othellier[i][tmp%TAILLE]==jj){
					trouve=1;	
					}
		tmp--;	
		}
		tmp++;
		if (trouve){
			for(x=tmp;x<=p;x++){
				othellier[i][x%TAILLE]=c;		 
			}		
		}
	}
	// vers le haut
	if ((p-TAILLE)>=0 && othellier[i-1][j]==ja){
		trouve=0;
		out=0;

	tmp=p-(2*TAILLE);
		while(trouve==0 && out==0){
				if (tmp<0)
					out=1;
				else if (othellier[tmp/TAILLE][j]==jj){
					trouve=1;

					}
		tmp-=TAILLE;	
		}
		tmp+=TAILLE;	
		if (trouve){
			for(x=tmp;x<=p;x=x+TAILLE){
				othellier[x/TAILLE][j]=c;		 
			}		
		}
	}
	// vers le bas
	if ((p+TAILLE)<NBCASES && othellier[i+1][j]==ja){
		trouve=0;
		out=0;

		tmp=p+(2*TAILLE);
		while(trouve==0 && out==0){
				if (tmp<0)
					out=1;
				else if (othellier[tmp/TAILLE][j]==jj){
					trouve=1;

					}
		tmp-=TAILLE;	
		}
		tmp+=TAILLE;	
		if (trouve){
			for(x=tmp;x>=p;x=x-TAILLE){
				othellier[x/TAILLE][j]=c;		 
			}		
		}
	}
	// diagonale haut droit
	if ((p-TAILLE)>0 && (p-TAILLE+1)/TAILLE==i-1 && othellier[i-1][j+1]==ja){
		trouve=0;
		out=0;
		cpt=i;
		tmp=p-2*TAILLE+2;
		while(trouve==0 && out==0){
				if (((p-TAILLE)<0) && ((p+1)/TAILLE!=cpt-1))
					out=1;
				else if (othellier[tmp/TAILLE][tmp%TAILLE]==jj){
					trouve=1;
					}
		tmp=tmp-TAILLE+1;
		cpt--;	
		}
		tmp=tmp+TAILLE-1;
		if(trouve){
			for(x=tmp;x<=p;x=x+TAILLE-1){
				othellier[x/TAILLE][x%TAILLE]=c;
			}
		}
	}
	// diagonale haut gauche
	if ((p-TAILLE)>0 && (p-TAILLE-1)/TAILLE==i-1 && othellier[i-1][j-1]==ja){
		trouve=0;
		out=0;
		cpt=i;
		tmp=p-2*TAILLE-2;
		while(trouve==0 && out==0){
				if ((tmp<0) && (tmp/TAILLE!=cpt-1))
					out=1;
				else if (othellier[tmp/TAILLE][tmp%TAILLE]==jj){
					trouve=1;
					}
		tmp=tmp-TAILLE-1;	
		cpt--;
		}
		tmp=tmp+TAILLE+1;
		if(trouve){
			for(x=tmp;x<=p;x=x+TAILLE+1){
				othellier[x/TAILLE][x%TAILLE]=c;
			}
		}
	}
	// diagonale bas gauche
	if ((p+TAILLE)<NBCASES && (p+TAILLE-1)/TAILLE==i+1 && othellier[i+1][j-1]==ja){
		trouve=0;
		out=0;
		cpt=i;
		tmp=p+2*TAILLE-2;
		while(trouve==0 && out==0){
				if (((p+TAILLE)<NBCASES) && ((p-1)/TAILLE!=cpt+1))
					out=1;
				else if (othellier[tmp/TAILLE][tmp%TAILLE]==jj){
					trouve=1;
					}
		tmp=tmp+TAILLE-1;
		cpt++;	
		}
		tmp=tmp-TAILLE+1;
		if(trouve){
			for(x=tmp;x>=p;x=x-TAILLE+1){
				othellier[x/TAILLE][x%TAILLE]=c;
			}
		}
	}
	// diagonale bas droit
	if ((p+TAILLE)<NBCASES && (p+TAILLE+1)/TAILLE==i+1 && othellier[i+1][j+1]==ja){
		trouve=0;
		out=0;
		cpt=i;
		tmp=p+2*TAILLE+2;
		while(trouve==0 && out==0){
				if (((p+TAILLE)<NBCASES) && ((p+1)/TAILLE!=cpt+1))
					out=1;
				else if (othellier[tmp/TAILLE][tmp%TAILLE]==jj){
					trouve=1;
					}
		tmp=tmp+TAILLE+1;	
		cpt++;
		}
		tmp=tmp-TAILLE-1;
		if(trouve){
			for(x=tmp;x>=p;x=x-TAILLE-1){
				othellier[x/TAILLE][x%TAILLE]=c;
			}
		}
	}		

}


int humanInput(){
	char letter, number;
	do{
		printf("azy donne ton choix laaa.\n");
		scanf(" %c%c",&letter,&number);

		printf("Letter : %d\n",letter-65);
		printf("number : %d\n",number-48);
		printf("Produit : %d\n",(number-48)*TAILLE + (letter-65));
		fflush(stdin);
		
	}while((letter<65 ||letter>72) || (number<48 || number>56));
	
	return ((number-48)*TAILLE + (letter-65));
}




/**
 * Fonction qui recalcule les nouvelles coordonnées d'un point
 * selon un décalage donnée par un vecteur
 */
void computeNextPoint(int * pointX, int * pointY, int Dx, int Dy){
	*pointX = *pointX + Dx;
	*pointY = *pointY + Dy;
}

