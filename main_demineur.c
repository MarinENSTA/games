/* PROJET IN103 : Démineur */ 

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct cas {
	int val;
	int boole;
} ;



/* Création de la grille du démineur */ 

struct cas** creer_grille(int dimension) {
	struct cas** tableau;
/* Pour fabriquer la grille, nous décidons d'utiliser un tableau de poiteurs soit un tableau à 2 dimensions. Cela nous permet une meilleure visualisation de la grille et de nous déplacer aisément dedans. */
	tableau=malloc(dimension*sizeof(struct cas));
	if(tableau==NULL) {
		printf("Error : memory allocation");
		exit(-1); 
	}
	for (int i=0;i<dimension;i++) {
		tableau[i]=malloc(dimension*sizeof(struct cas));
		if(tableau[i]==NULL) {
			printf("Error : memory allocation");
			exit(-1);
		}
	}

	int i,j;
	for (i=0;i<dimension;i++){
		for (j=0;j<dimension;j++){
			tableau[i][j].val=0;
			tableau[i][j].boole=0;
		}
	}
	return tableau;
}


/* Cette fonction "display" permet l'affichage de la grille de démineur dans le terminal
Elle est programmée pour des tableaux allant jusqu'à la taille 999*999.
Malheureusement les écrans utilisés ne permettront jamais l'affichage correct de telles grilles :
En pratique, au delà de 50*50 pour un ordinateur de taille normale, le jeu devient compliqué à jouer.
C'est là une des limites causée par le fait d'utiliser le terminal comme affichage graphique. */

void display(struct cas** table, int dim){
	int i,j;
    int c = 0;

    printf("    ");
    for (c=0;c<dim;c++){
    	printf("%d",c); //on inscrit les coordonnées sur les bords de la grille (ici, ligne au dessus)
    	printf(" ");
    	if (c<100){ // Il est nécessaire de prendre ces cas en compte pour éviter les décages, à grande dimension.
    		printf(" ");
    		if (c<10){ //Les décalages apparaissent dès le passage entre N<10 et N>=10
    			printf(" ");
    		}
    	}
    }

  	c = 0;
  	printf("\n");

  	for(i=0;i<dim;i++){
    	printf("%d ",c); //Affichage du numéro de ligne à chaque début de ligne

    	if (c<100){ // Ici aussi, on est attentif au décalage provoqué par le passage aux dizaines et aux centaines
    		printf(" "); 
    		if (c<10){
    			printf(" ");
    		}
    	}


    	c++;
    	for(j=0;j<dim;j++){
    		
    		if(table[i][j].boole==1){
    			printf("%d   ",table[i][j].val);	
    		}
    		else{
    			printf("XXX "); // "XXX" correspond à une case non visible actuellement (On prend ces trois caractères parce qu'ils sont plus visibles dans le terminal)
    		}
    	}
    	printf("\n");
    }
  	printf("\n");
}



/* Placement des bombes en début de partie. */

void placement(struct cas** tableau, int dim, int mines){
	srand(time(0));
    int i = 0 ;
    while (i < mines){
		/* On choisit une case aléatoirement et on va y placer une bombe*/
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
/* Lorsqu'on place une bombe on fait "+1" sur les huits cases autour. Cependant il faut tester si la bombe est sur une arête ou dans un coin car elle n'aura alors plus 8 voisins. */
    int j,k;
	for (j=0;j<dim;j++){
		for (k=0;k<dim;k++){
			if(tableau[j][k].val>9){tableau[j][k].val=9;}
/* Après tout le processus placement, on applique un seuillage à 9. Aussi 9 représentera une bombe et les chiffres allant de 1 à 8 représenteront les bombes voisines des cases. */
		}
	}
}


/* Passer les cases en "à afficher" (case où on a cliqué et celles vides annexes aussi) */

/* x et y sont les coordonnées de la case sur laquelle on a cliquée */
/* l'objectif de cette fonction est de remplir la fonctionnalité du démineur suivant : lorsque l'on clique sur une case avec aucune bombe autour, alors tout une zone autour se developpe des cases sans bombes autour avec une frontière de cases chiffrées (avec des bombes autour) */

void propagation(struct cas** tableau,int x, int y,int dimension) {
	tableau[x][y].boole=1;
	
	/* La fonction ne doit agir que si la case cliquée est un 0 : dans les autres cas, il n'y a aucune raison de donner d'autres informations au joueur */
	if (tableau[x][y].val==0) {

	/* L'ensemble des tests suivants servent à : traiter les cas particuliers (coins et bords) et dans chacun de ces cas, regarder les cases voisines pour voir : (i) si elles sont vides et donc appliquer la propagation
	 * 																																							  (ii) si elles sont voisines de bombes pour juste les afficher */
		if (x==0 && y==0) {                                                   /* coin haut gauche */
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

		else if (x==dimension-1 && y==0) {                                     /* coin bas gauche */
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

		else if (x==dimension-1 && y==dimension-1) {                         /* coin bas droit */
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

		else if (x==0 && y==dimension-1) {                                 /* coin haut droit */
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

		else if (x==0 && y!=0 && y!=dimension-1) {                          /* bord haut (sans coins) */
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

		else if (x==dimension-1 && y!=0 && y!=dimension-1) {                    /* bord bas(sans coins) */
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

		else if (y==dimension-1 && x!=0 && x!=dimension-1) {                      /* bord droit (sans coins) */
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

		else if (y==0 && x!=0 && x!=dimension-1) {                            /* bord gauche (sans coins) */
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
		
		else {                                                                 /* case quelconque au coeur de la grille */
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


/* Cette fonction "victoire" vérifie simplement si le nombre de cases non-affichees restantes correspond au nombre de mines
Ainsi, si on atteint le point où a autant  de cases non-affichées que de mines, on a nécessairement gagné (autrement, on aurait forcement perdu avant !) 

NB : cet algorithme de vérification de la condition de victoire n'est pas optimal et nous en sommes conscients : il parcoure la grille entièrement à chaque tour
Pour mieux faire, il aurait fallu utiliser un simple variable int initialisée au nombre total de cases de la grille, décrémentée pour chaque case découverte */ 
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

/* Cette fonction "tour" est la le coeur de notre algorithme : elle verifie sans cesse les conditions de victoire (ou de défaite), et découvre des cases 
à l'aide de la fonction "propagation" */ 
int tour(struct cas** table,int N,int mines, int end) {
	display(table,N);

	int l,c;
	printf("Ligne : ");
	scanf("%d",&l);
	printf("Colonne : ");
	scanf("%d",&c);

	if (table[l][c].val==9){
		end=-1;
	}
	else {propagation(table,l,c,N);}
	return end;
}

// Le main, qui regroupe toutes les fonctions. 
// Nous avons choisi d'y faire figurer toutes les chaînes de caractère à imprimer en début de partie, plutot que de le faire dans une fonction annexe.
int main(){

	printf("Bonjour et bienvenue dans votre demineur-terminal prefere !\nUn projet de Marin STAMM, Grégoire BRIVARY, Nathan FAGANELLO, Baptiste LOIRE\n\n");
	printf("Nous vous recommandons de mettre le terminal en plein écran pour une expérience de jeu optimale !\n");
	
	printf("Commençons par initialiser votre grille de démineur... Ne voyez pas trop grand !\n\n");
    printf("Par exemple, voici 3 exemples de niveaux à difficulté croissante :\n");
    printf("FACILE dimension 8x8 -> 10 mines\n");
    printf("MOYEN dimension 16x16 -> 40 mines\n");
    printf("DIFFICILE dimension 22x22 -> 99 mines\n\n");

	int N=0;
	int mines=0;

	printf("Dimension de votre grille : "); // Initialisation de la taille de la grille.
	scanf("%d", &N);
	while(N<2){
		printf("Dimension incorrecte...\n");
		
		printf("Dimension de votre grille : ");
		scanf("%d", &N);
	}

	printf("Nombre de mines : "); //Initialisation du nombre de mines
	scanf("%d", &mines);
	while (mines>N*N){
		printf("Il y a trop de mines... C'est dangereux !\n");
		
		printf("Nombre de mines : ");
		scanf("%d", &mines);
	}

	printf("Début de la partie ! Good luck...\n");

	int end=0;
	struct cas** table=creer_grille(N);
	placement(table,N,mines);



	while (end==0){ // l'essentiel de la partie tient... dans cette boucle !
		end=tour(table,N,mines,end);
		if (end>=0){
			end=victoire(table,N,mines,end);
		}
	}


	if (end==-1){
		printf("BOUM, c'était une mine, perdu !\n");
	}

	if (end==1){
		display(table,N);
		printf ("La grille est finie, félicitations !\n");
	}
	// Apres la victoire, ou la defaite, le programme se termine aussitot. 
	// on aurait pu songer a faire une requete de type "Recommencer ? (y/n)"

	return(0);

}


