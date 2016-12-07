#include <stdio.h>
#include <assert.h>
#include <malloc.h>

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
void cases_occupes(int T[],char J);
void coup_jouable(int T[], int R[], char c);
void change_othellier(int p,char c);
int humanInput();

char othellier[TAILLE][TAILLE] ;



int main(){
	initialization();
	while(1){
		printGameWithHelp('N');
		change_othellier(humanInput(),'N');
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
	int casesOccuppees[NBCASES],coupsJouables[NBCASES];
	cases_occupes(casesOccuppees,couleur);
	coup_jouable(casesOccuppees,coupsJouables,couleur);

	
	
	int i,caseJouable,k;
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
			k=0;
			caseJouable=0;
			while(!caseJouable && k<NBCASES){
				if(coupsJouables[k]==i){
					caseJouable = 1;
				}
				k++;
			}
			if(caseJouable){
				printf(" %sV%s ",YELLOWCOLOR,NORMALCOLOR);
			}else{
				printf(" V ");
			}
		}
	}
	printf("%d\n",TAILLE-1);
}

void cases_occupes(int T[],char J){	//Le tableau T se remplis desnumeros de cases occupées par le joueur J   
	int accu=0,i;
	for(i=0; i<NBCASES;i++){
		if(othellier[i/TAILLE][i%TAILLE]==J){
			T[accu]=i;
			accu++;
		}
	}
	for (i=accu;i<NBCASES;i++){
		T[i]=-1;
	}

	printf("\n");
}
void coup_jouable(int T[], int R[], char c){	//Le tableau R se remplis des positions ou le joueur désigné par c peut jouer 
	char ja;
	int i,j,p=0,trouve,out,tmp,accu=0,cpt;
	
	if (c=='N')ja='B'; else ja='N';
	while(p<NBCASES && T[p]!=-1){
		
		i=T[p]/TAILLE;	//ligne de p		
		j=T[p]%TAILLE;	//colonne de p
		
		// vers la droite
		if ((T[p]+1)/TAILLE==i && othellier[i][j+1]==ja){
			
			trouve=0;
			out=0;
			tmp=T[p]+2;
			while(trouve==0 && out==0){
					if (tmp/TAILLE!=i)
						out=1;
					else if (othellier[i][tmp%TAILLE]=='V'){
						trouve=1;	
						R[accu]=tmp;
						accu++;
						}
			tmp++;	
			}	
		}
		//vers la gauche
		if ((T[p]-1)/TAILLE==i && othellier[i][j-1]==ja){
			trouve=0;
			out=0;
			tmp=T[p]-2;
			while(trouve==0 && out==0){
					if (tmp/TAILLE!=i)
						out=1;
					else if (othellier[i][tmp%TAILLE]=='V'){
						trouve=1;	
						R[accu]=tmp;
						accu++;
						}
			tmp--;	
			}	
		}
		//vers le haut
		if ((T[p]-TAILLE)>=0 && othellier[i-1][j]==ja){
			trouve=0;
			out=0;
			tmp=T[p]-(2*TAILLE);
			while(trouve==0 && out==0){
					if (tmp<0)
						out=1;
					else if (othellier[tmp/TAILLE][j]=='V'){
						trouve=1;	
						R[accu]=tmp;
						accu++;
						}
			tmp-=TAILLE;	
			}	
		}
		//vers le bas
		if ((T[p]+TAILLE)<NBCASES && othellier[i+1][j]==ja){
			trouve=0;
			out=0;
			tmp=T[p]+(2*TAILLE);
			while(trouve==0 && out==0){
					if (tmp>NBCASES)
						out=1;
					else if (othellier[tmp/TAILLE][j]=='V'){
						trouve=1;	
						R[accu]=tmp;
						accu++;
						}
			tmp+=TAILLE;	
			}	
		}
		// diagonale haut droit
		if ((T[p]-TAILLE)>0 && (T[p]-TAILLE+1)/TAILLE==i-1 && othellier[i-1][j+1]==ja){
			trouve=0;
			out=0;
			cpt=i;
			tmp=T[p]-2*TAILLE+2;
			while(trouve==0 && out==0){
					if (((T[p]-TAILLE)<0) && ((T[p]+1)/TAILLE!=cpt-1))
						out=1;
					else if (othellier[tmp/TAILLE][tmp%TAILLE]=='V'){
						trouve=1;
						R[accu]=tmp;
						accu++;
						}
			cpt--;
			tmp=tmp-TAILLE+1;	
			}		
		}
		// diagonale haut gauche
		if ((T[p]-TAILLE)>0 && (T[p]-TAILLE-1)/TAILLE==i-1 && othellier[i-1][j-1]==ja){
			trouve=0;
			out=0;
			cpt=i;
			tmp=T[p]-2*TAILLE-2;
			while(trouve==0 && out==0){
					if (((T[p]-TAILLE)<0) && ((T[p]-1)/TAILLE!=cpt-1))
						out=1;
					else if (othellier[tmp/TAILLE][tmp%TAILLE]=='V'){
						trouve=1;
						R[accu]=tmp;
						accu++;
						}
			tmp=tmp-TAILLE-1;	
			cpt--;
			}		
		}
		// diagonale bas droite
		if ((T[p]+TAILLE)<NBCASES && (T[p]+TAILLE+1)/TAILLE==i+1 && othellier[i+1][j+1]==ja){
			trouve=0;
			out=0;
			cpt=0;
			tmp=T[p]+2*TAILLE+2;	
			while(trouve==0 && out==0){
					if (((T[p]+TAILLE)>NBCASES) && ((T[p]+1)/TAILLE!=cpt+1))
						out=1;
					else if (othellier[tmp/TAILLE][tmp%TAILLE]=='V'){
						trouve=1;	
						R[accu]=tmp;
						accu++;
						}
			tmp=tmp+TAILLE+1;
			cpt++;	
			}		
		}
		// diagonale bas gauche
		if ((T[p]+TAILLE)<NBCASES && (T[p]+TAILLE-1)/TAILLE==i+1 && othellier[i+1][j-1]==ja){
			trouve=0;
			out=0;
			tmp=T[p]+2*TAILLE-2;
			while(trouve==0 && out==0){
					if (((T[p]+TAILLE)>NBCASES) && ((T[p]-1)/TAILLE!=cpt+1))
						out=1;
					else if (othellier[tmp/TAILLE][tmp%TAILLE]=='V'){
						trouve=1;
						R[accu]=tmp;
						accu++;
						}
			tmp=tmp+TAILLE-1;
			cpt++;	
			}		
		}
	
	p++;
	}
	for(i=accu;i<NBCASES;i++){
		R[i]=-1;
	}
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
		scanf("%c%c",&letter,&number);
	}while((letter<65 ||letter>72) || (number<48 || number>56));
	
	return ((number-48)*TAILLE + (letter-65));
}

