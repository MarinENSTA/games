/* PROJET IN103 : Démineur */ 

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "minesweeperModule.h"




/* Création de la grille du démineur */ 
struct cas** creer_grille(int dimension) {
	struct cas** tableau;
	tableau=malloc(dimension*sizeof(struct cas));
	if(tableau==NULL) {
		printf("Error : memory allocation");
		exit(1); 
	}
	for (int i=0;i<dimension;i++) {
		tableau[i]=malloc(dimension*sizeof(struct cas));
		if(tableau[i]==NULL) {
			printf("Error : memory allocation");
			exit(1);
		}
	}

	int i,j;
	for (i=0;i<dimension;i++){
		for (j=0;j<dimension;j++){
			tableau[i][j].val=0;
			tableau[i][j].boole=0;
			tableau[i][j].flagged=0;
		}
	}
	return tableau;
}

void display(struct cas** table, int dim){
	int i,j;
    int c = 0;

    printf("    ");
    for (c=0;c<dim;c++){
    	printf("%d",c);
    	printf(" ");
    	if (c<100){
    		printf(" ");
    		if (c<10){
    			printf(" ");
    		}
    	}
    }

  	c = 0;
  	printf("\n");

  	for(i=0;i<dim;i++){
    	printf("%d ",c);

    	if (c<100){
    		printf(" ");
    	}

    	if (c<10){
    		printf(" ");
    	}
    	c++;
    	for(j=0;j<dim;j++){
    		
    		if(table[i][j].boole==1){
    			printf("%d   ",table[i][j].val);	
    		}
    		else{
    			printf("XXX ");
    		}
    	}
    	printf("\n");
    }
  	printf("\n");
}


/* Placement des bombes */

void placement(struct cas** tableau, int dim, int mines){
	srand(time(0));
    int i = 0 ;



    while (i < mines){
        int m = rand() % dim ;
        int n = rand() %dim ;
        if (tableau[n][m].val < 10){
            tableau[n][m].val = 10 ;
            if (m == 0 && n == 0){
                tableau[n+1][m].val++ ;
                tableau[n][m+1].val++ ;
                tableau[n+1][m+1].val++ ;
            }
            else if (n == 0 && m == dim-1 ){
                tableau[n+1][m].val++ ;
                tableau[n][m-1].val++ ;
                tableau[n+1][m-1].val++ ;
            }
            else if (n == dim-1 && m == 0){
                tableau[n][m+1].val++ ;
                tableau[n-1][m].val++ ;
                tableau[n-1][m+1].val++ ;
            }
            else if (n == dim-1 && m == dim-1){
                tableau[n][m-1].val++ ;
                tableau[n-1][m].val++ ;
                tableau[n-1][m-1].val++ ;
            }
            else if (n == 0){
                tableau[n+1][m].val++ ;
                tableau[n][m+1].val++ ;
                tableau[n+1][m+1].val++ ;
                tableau[n][m-1].val++ ;
                tableau[n+1][m-1].val++ ;
            }
            else if (n == dim-1){
                tableau[n][m+1].val++ ;
                tableau[n-1][m].val++ ;
                tableau[n-1][m+1].val++ ;
                tableau[n][m-1].val++ ;
                tableau[n-1][m-1].val++ ;
            }
            else if (m == 0){
                tableau[n][m+1].val++ ;
                tableau[n-1][m].val++ ;
                tableau[n-1][m+1].val++ ;
                tableau[n+1][m].val++ ;
                tableau[n+1][m+1].val++ ;
            }
            else if (m == dim-1){
                tableau[n][m-1].val++ ;
                tableau[n-1][m].val++ ;
                tableau[n-1][m-1].val++ ;
                tableau[n+1][m-1].val++ ;
                tableau[n+1][m].val++ ;
            }
            else{
                tableau[n][m-1].val++ ;
                tableau[n][m+1].val++ ;
                tableau[n-1][m].val++ ;
                tableau[n+1][m].val++ ;
                tableau[n+1][m+1].val++ ;
                tableau[n+1][m-1].val++ ;
                tableau[n-1][m-1].val++ ;
                tableau[n-1][m+1].val++ ;
            }
            i++ ;
        }
    }
    int j,k;
	for (j=0;j<dim;j++){
		for (k=0;k<dim;k++){
			if(tableau[j][k].val>9){tableau[j][k].val=9;}
		}
	}
}


/* Passer les cases en "à afficher" (case où on a cliqué et celles vides annexes aussi) */

/* x et y sont les coordonnées de la case sur laquelle on a cliquée
 * tableau_entiers est le tableau avec des 0 ->case vide sans bombe autour, 10 -> bombe ou (1,...,8) -> vide avec k bombes autour
 * tableau_bool est un tableau de 0 ou 1 avec 0 -> ne pas afficher, 1 -> afficher*/

void propagation(struct cas** tableau,int x, int y,int dimension) {
	tableau[x][y].boole=1;
	
	if (tableau[x][y].val==0) {

		if (x==0 && y==0) {
			if (tableau[x+1][y].val==0 && tableau[x+1][y].boole==0) {
				propagation(tableau,x+1,y,dimension);
			}
			if (tableau[x][y+1].val==0 && tableau[x][y+1].boole==0) {
				propagation(tableau,x,y+1,dimension);
			}
			if (tableau[x][y+1].val>0 && tableau[x][y+1].val<8) {
				tableau[x][y+1].boole=1;
			}
			if (tableau[x+1][y].val>0 && tableau[x+1][y].val<8) {
				tableau[x+1][y].boole=1;
			}
			if (tableau[x+1][y+1].val>0 && tableau[x+1][y+1].val<8) {
				tableau[x+1][y+1].boole=1;
			}
		}

		else if (x==dimension-1 && y==0) {
			if (tableau[x-1][y].val==0 && tableau[x-1][y].boole==0) {
				propagation(tableau,x-1,y,dimension);
			}
			if (tableau[x][y+1].val==0 && tableau[x][y+1].boole==0) {
				propagation(tableau,x,y+1,dimension);
			}
			if (tableau[x-1][y].val>0 && tableau[x-1][y].val<8) {
				tableau[x-1][y].boole=1;
			}
			if (tableau[x][y+1].val>0 && tableau[x][y+1].val<8) {
				tableau[x][y+1].boole=1;
			}
			if (tableau[x-1][y+1].val>0 && tableau[x-1][y+1].val<8) {
				tableau[x-1][y+1].boole=1;
			}
		}

		else if (x==dimension-1 && y==dimension-1) {
			if (tableau[x-1][y].val==0 && tableau[x-1][y].boole==0) {
				propagation(tableau,x-1,y,dimension);
			}
			if (tableau[x][y-1].val==0 && tableau[x][y-1].boole==0) {
				propagation(tableau,x,y-1,dimension);
			}
			if (tableau[x-1][y].val>0 && tableau[x-1][y].val<8) {
				tableau[x-1][y].boole=1;
			}
			if (tableau[x][y-1].val>0 && tableau[x][y-1].val<8) {
				tableau[x][y-1].boole=1;
			}
			if (tableau[x-1][y-1].val>0 && tableau[x-1][y-1].val<8) {
				tableau[x-1][y-1].boole=1;
			}
		}

		else if (x==0 && y==dimension-1) {
			if (tableau[x][y-1].val==0 && tableau[x][y-1].boole==0) {
				propagation(tableau,x,y-1,dimension);
			}
			if (tableau[x+1][y].val==0 && tableau[x+1][y].boole==0) {
				propagation(tableau,x+1,y,dimension);
			}
			if (tableau[x][y-1].val>0 && tableau[x][y-1].val<8) {
				tableau[x][y-1].boole=1;
			}
			if (tableau[x+1][y].val>0 && tableau[x+1][y].val<8) {
				tableau[x+1][y].boole=1;
			}
			if (tableau[x+1][y-1].val>0 && tableau[x+1][y-1].val<8) {
				tableau[x+1][y-1].boole=1;
			}
		}

		else if (x==0 && y!=0 && y!=dimension-1) {
			if (tableau[x][y-1].val==0 && tableau[x][y-1].boole==0) {
				propagation(tableau,x,y-1,dimension);
			}
			if (tableau[x][y+1].val==0 && tableau[x][y+1].boole==0) {
				propagation(tableau,x,y+1,dimension);
			}
			if (tableau[x+1][y].val==0 && tableau[x+1][y].boole==0) {
				propagation(tableau,x+1,y,dimension);
			}
			if (tableau[x][y-1].val>0 && tableau[x][y-1].val<8) {
				tableau[x][y-1].boole=1;
			}
			if (tableau[x][y+1].val>0 && tableau[x][y+1].val<8) {
				tableau[x][y+1].boole=1;
			}
			if (tableau[x+1][y].val>0 && tableau[x+1][y].val<8) {
				tableau[x+1][y].boole=1;
			}
			if (tableau[x+1][y-1].val>0 && tableau[x+1][y-1].val<8) {
				tableau[x+1][y-1].boole=1;
			}
			if (tableau[x+1][y+1].val>0 && tableau[x+1][y+1].val<8) {
				tableau[x+1][y+1].boole=1;
			}
		}

		else if (x==dimension-1 && y!=0 && y!=dimension-1) {
			if (tableau[x][y-1].val==0 && tableau[x][y-1].boole==0) {
				propagation(tableau,x,y-1,dimension);
			}
			if (tableau[x][y+1].val==0 && tableau[x][y+1].boole==0) {
				propagation(tableau,x,y+1,dimension);
			}
			if (tableau[x-1][y].val==0 && tableau[x-1][y].boole==0) {
				propagation(tableau,x-1,y,dimension);
			}
			if (tableau[x][y-1].val>0 && tableau[x][y-1].val<8) {
				tableau[x][y-1].boole=1;
			}
			if (tableau[x][y+1].val>0 && tableau[x][y+1].val<8) {
				tableau[x][y+1].boole=1;
			}
			if (tableau[x-1][y].val>0 && tableau[x-1][y].val<8) {
				tableau[x-1][y].boole=1;
			}
			if (tableau[x-1][y-1].val>0 && tableau[x-1][y-1].val<8) {
				tableau[x-1][y-1].boole=1;
			}
			if (tableau[x-1][y+1].val>0 && tableau[x-1][y+1].val<8) {
				tableau[x-1][y+1].boole=1;
			}
		}

		else if (y==dimension-1 && x!=0 && x!=dimension-1) {
			if (tableau[x-1][y].val==0 && tableau[x-1][y].boole==0) {
				propagation(tableau,x-1,y,dimension);
			}
			if (tableau[x+1][y].val==0 && tableau[x+1][y].boole==0) {
				propagation(tableau,x+1,y,dimension);
			}
			if (tableau[x][y-1].val==0 && tableau[x][y-1].boole==0) {
				propagation(tableau,x,y-1,dimension);
			}
			if (tableau[x-1][y].val>0 && tableau[x-1][y].val<8) {
				tableau[x-1][y].boole=1;
			}
			if (tableau[x+1][y].val>0 && tableau[x+1][y].val<8) {
				tableau[x+1][y].boole=1;
			}
			if (tableau[x][y-1].val>0 && tableau[x][y-1].val<8) {
				tableau[x][y-1].boole=1;
			}
			if (tableau[x-1][y-1].val>0 && tableau[x-1][y-1].val<8) {
				tableau[x-1][y-1].boole=1;
			}
			if (tableau[x+1][y-1].val>0 && tableau[x+1][y-1].val<8) {
				tableau[x+1][y-1].boole=1;
			}
		}

		else if (y==0 && x!=0 && x!=dimension-1) {
			if (tableau[x-1][y].val==0 && tableau[x-1][y].boole==0) {
				propagation(tableau,x-1,y,dimension);
			}
			if (tableau[x+1][y].val==0 && tableau[x+1][y].boole==0) {
				propagation(tableau,x+1,y,dimension);
			}
			if (tableau[x][y+1].val==0 && tableau[x][y+1].boole==0) {
				propagation(tableau,x,y+1,dimension);
			}
			if (tableau[x-1][y].val>0 && tableau[x-1][y].val<8) {
				tableau[x-1][y].boole=1;
			}
			if (tableau[x+1][y].val>0 && tableau[x+1][y].val<8) {
				tableau[x+1][y].boole=1;
			}
			if (tableau[x][y+1].val>0 && tableau[x][y+1].val<8) {
				tableau[x][y+1].boole=1;
			}
			if (tableau[x-1][y+1].val>0 && tableau[x-1][y+1].val<8) {
				tableau[x-1][y+1].boole=1;
			}
			if (tableau[x+1][y+1].val>0 && tableau[x+1][y+1].val<8) {
				tableau[x+1][y+1].boole=1;
			}
		}
		
		else {
			if (tableau[x-1][y].val==0 && tableau[x-1][y].boole==0) {
				propagation(tableau,x-1,y,dimension);
			}
			if (tableau[x+1][y].val==0 && tableau[x+1][y].boole==0) {
				propagation(tableau,x+1,y,dimension);
			}
			if (tableau[x][y+1].val==0 && tableau[x][y+1].boole==0) {
				propagation(tableau,x,y+1,dimension);
			}
			if (tableau[x][y-1].val==0 && tableau[x][y-1].boole==0) {
				propagation(tableau,x,y-1,dimension);
			}
			if (tableau[x-1][y].val>0 && tableau[x-1][y].val<8) {
				tableau[x-1][y].boole=1;
			}
			if (tableau[x+1][y].val>0 && tableau[x+1][y].val<8) {
				tableau[x+1][y].boole=1;
			}
			if (tableau[x][y+1].val>0 && tableau[x][y+1].val<8) {
				tableau[x][y+1].boole=1;
			}
			if (tableau[x][y-1].val>0 && tableau[x][y-1].val<8) {
				tableau[x][y-1].boole=1;
			}
			if (tableau[x-1][y-1].val>0 && tableau[x-1][y-1].val<8) {
				tableau[x-1][y-1].boole=1;
			}
			if (tableau[x+1][y-1].val>0 && tableau[x+1][y-1].val<8) {
				tableau[x+1][y-1].boole=1;
			}
			if (tableau[x+1][y+1].val>0 && tableau[x+1][y+1].val<8) {
				tableau[x+1][y+1].boole=1;
			}
			if (tableau[x-1][y+1].val>0 && tableau[x-1][y+1].val<8) {
				tableau[x-1][y+1].boole=1;
			}
		}
	}
}

int victoire(struct cas** table,int N,int mines,int end){
	int i,j;
	int k=0;
	for (i=0;i<N;i++){
		for (j=0;j<N;j++){
			if (table[i][j].boole==0){
				k=k+1;
			}
		}
	}
	if (k==mines){
		end=1;
	}
	return end;
}

int tour(struct cas** table,int N,int mines, int end) {
	display(table,N);

	int l,c;
	printf("Ligne : ");
	scanf("%d",&l);
	printf("Colonne : ");
	scanf("%d",&c);

	end = victoire(table,N,mines,end);
	if (table[l][c].val==9){
		end=-1;
	}

	if (end == 0)
		propagation(table,l,c,N);

	return end;
}

int sdltour(struct cas** table,int N,int mines, int end, int l,int c)
{
	end = victoire(table,N,mines,end);
	if (table[l][c].val==9){
		end=-1;
	}
	else {propagation(table,l,c,N);}
	return end;
}