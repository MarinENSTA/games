#ifndef __MINESWEEPERMODULE_H__
#define __MINESWEEPERMODULE_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct cas {
	int val;
	int boole;
	int flagged;
} ;

struct cas** creer_grille(int dimension);
void display(struct cas** table, int dim);
void placement(struct cas** tableau, int dim, int mines);
void propagation(struct cas** tableau,int x, int y,int dimension);
int victoire(struct cas** table,int N,int mines,int end);
int tour(struct cas** table,int N,int mines, int end);
int sdltour(struct cas** table,int N,int mines, int end, int l,int c);


#endif