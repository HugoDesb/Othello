/**
 * @author DESBIOLLES Hugo <hugo.desbiolles@etu.univ-amu.fr>
 * @author VILLA Gabriel <gabriel.villa@etu.univ-amu.fr>
 */

/**
 * @file main.c
 */




#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#define TAILLE 8
#define NBCASES 64

#define KNRM  "\x1B[0"
#define KBLK  "\033[22;30m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int main();
void initialization();
void printGame();

// ‘N’ = Noir; ‘B’ = Blanc; ‘V’ = Case Vide; 
char othellier[TAILLE][TAILLE] ;

int main()
{
	initialization();
	do{
		printGame();
		Played1 =1;
		Played2 =1;

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

void printGame(){
	int i;
	for(i=0; i<NBCASES;i++){
		if(i%TAILLE == 0){
			printf("\n");
		}
		printf(" %c ",othellier[i/8][i%8]);	
	}
	printf("\n");
}



