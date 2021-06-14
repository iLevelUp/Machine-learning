#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "struct.h"
#include "liste.h"

/**
* @method addBMU : Insère un noeud BMU au début de liste
* @param {pos *} bmuL:  Donnée de la liste, ici les positions
* @param {int} l: Donnée du noeud à ajouter
* @param {int} c: Donnée du noeud à ajouter
*/
pos *addBMU(pos *bmuL, int l, int c){
	pos *newBmu = (pos*)malloc(sizeof(pos));

	newBmu->l =l;
	newBmu->c =c;
	newBmu->next = bmuL;

	return newBmu;
}

/**
* @method push : Insère un noeud BMU au début de liste
* @param {pos **} bmuL:  Donnée de la liste, ici les positions
* @param {int} l: Donnée du noeud à ajouter
* @param {int} c: Donnée du noeud à ajouter
*/
void push(pos** bmuL, int l, int c){ 

    pos * newNode = (pos*)malloc(sizeof(pos));;
  
    newNode->l  = l;
    newNode->c = c;
  

    newNode->next = (*bmuL); 
    (*bmuL) = newNode; 
} 

/**
* @method randList : Tire un noeud aléatoirement
* @param {pos *} bmuL:  Donnée de la liste, ici les positions
* @param {int} n: taille de la liste
*/
pos randList(pos *bmuL,int n){
	pos res = {0, 0};
	pos *current = bmuL; 
	int al = rand() % (n+1);
	int it = 0;
	while(current){

		if(it == al){
			res.l = current->l;
			res.c = current->c;
			break;
		}

		current = current->next;
		it++;
	}
	return res;
}

/**
* @method freeList : Prend une liste et l'efface
* @param {pos *} bmuL: La liste
*/
pos * freeList(pos * bmuL) {
	//printf("bmuStart\n");
	pos * ptrl2 = bmuL;

	if(bmuL == NULL)
		return bmuL;

	while(bmuL) {
		ptrl2 = bmuL;
		bmuL = bmuL->next;
		free(ptrl2);
	}
	//printf("-- bmuEnd\n");
	return bmuL;
}

void print_list(pos * bmuL) {
  if(!bmuL)
    return;

  while(bmuL) {
    printf("%d, %d -> ", bmuL->l, bmuL->c);
    bmuL = bmuL->next;
  }
  printf("NULL\n");
}