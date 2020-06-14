/* PROJET IN103 : Démineur */ 

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "minesweeperModule.h"

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


