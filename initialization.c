#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "math.h"
#include "initialization.h"
#include "struct.h"
#include "parser.h"
#include "learning.h"

/**
* @method normalization : Normalisation de notre base de données
* @param {struct *} dataBase: La base de donnée ou sera stockée les données du fichier récupéré
* @param {int} iriSize: La  taille de notre base de données
* @param {int} vectSize: La taille du vecteur de doubles
*/
void normalization(iris *dataBase, int iriSize, int vectSize){
	int i,j,k;
	for(i = 0; i < iriSize; ++i){	
		dataBase[i].norme = 0;	
		for(j = 0; j < vectSize ; ++j)
			dataBase[i].norme += pow(dataBase[i].v[j],2);
		dataBase[i].norme = sqrt(dataBase[i].norme);
		for(k = 0; k < vectSize ;++k)
			dataBase[i].v[k] /= dataBase[i].norme;
	}
}

/**
* @method shuffle : Prends un tableau et le mélange
* @param {int *} tb: Tableau d'entier
* @param {int} iriSize : Taille du tableau
*/
void shuffle (int *tb, int iriSize){
	int i, nbA, tmp;
	int test = 0;
	for(i = 0 ; i < iriSize ; ++i){
		nbA = rand()%iriSize;
		do{
			nbA = rand() %iriSize;
			for(int j = 0;j<i;++j){
				if(tb[j]==tb[nbA]){
					test =1;
					break;
				}
				else test = 0;
			}
		}while(test ==1);
		tmp = tb[i];
		tb[i] = tb[nbA];
		tb[nbA] = tmp;
	}
}

/**
* @method filler : Remplis un tableau de 1 à N
* @param {int} iriSize: La taille du tableau
*/
int *filler(int iriSize){
	int *tInd = calloc(iriSize,sizeof *tInd);
    for (int i = 0; i < iriSize; ++i)
        tInd[i] = i;
    return tInd;
}


/**
* @method VectMoyen : Calcule le vecteur moyen de la base de donnée
* @param {struct *} dataBase: La base de donnée
* @param {int} iriSize: La taille de la base de donnée
* @param {int} vectSize: La taille du vecteur de doubles
*/
iris vectMoyen(iris *dataBase, int iriSize, int vectSize){
	iris *vectMoy = (iris *)malloc(1*sizeof(iris));
	vectMoy->v = calloc(vectSize, sizeof(double)); 
	int i,j;

	for(i = 0; i < vectSize ; ++i){
		for(j = 0; j < iriSize;++j)
			vectMoy->v[i] += dataBase[j].v[i];
		vectMoy->v[i] /= iriSize;
	}
	return vectMoy[0];
}	