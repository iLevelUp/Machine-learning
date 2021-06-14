#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "time.h"
#include "math.h"
#include "ctype.h"
#include "initialization.h"
#include "struct.h"
#include "learning.h"
#include "liste.h"


/**
* @method vecteurNeurone : Remplis la map de neurones initialisés autour du vecteur au moyen
* @param {neuron **} network: Map de neurones
* @param {iris *} vectMoyen: Vecteur de moyen
* @param {int} vectSize: Taille du vecteur de doubles
* @param {double} vMin: mini
* @param {double} vMax: maxi
*/
void vecteurNeurone(neuron **network, iris vectMoyen, int vectSize, double vMin, double vMax){
	int i,j,h;
	for(i  = 0 ; i < NL ; ++i){
		for(j = 0;j < NC; ++j){
			for (h = 0; h < vectSize ; ++h){
				network[i][j].w[h]= (rand()/(double)RAND_MAX) * ((vectMoyen.v[h] + vMax)-(vectMoyen.v[h] - vMin)) + vectMoyen.v[h] - vMin;
			}
		}
	}
}

/**
* @method distEuclidienne : Calcule la distance euclidienne entre deux vecteurs de double
* @param {iris} dataBase: un element de la base de donnée.
* @param {double *} vector: vecteur de doubles
* @param {int} vectSize: Taille du vecteur de doubles
*/
double distEuclidienne(iris dataBase, double* vector, int vectSize){
    int i;
    double dist = 0;
    for (i = 0; i < vectSize; ++i)
        dist += pow((dataBase.v[i] - vector[i]),2);
    dist = sqrt(dist);
    return dist;
}

/**
* @method BMU : Trouve la position du BMU entre un vecteur tiré et la map
* @param {neuron **} network: Map de neurones
* @param {iris } drawnVector: Vecteur de la base de donnée tiré
* @param {int} vectSize: Taille du vecteur de doubles,
*/
pos BMU(iris drawnVector, neuron **network,int vectSize){
	int i,j;
	int sizeBMU = 1;
	int iBMU=0;
	double tmp,dist;
	pos *bmuTMP = (pos*) malloc(sizeBMU * sizeof(pos));
	pos bmu;
	tmp = 10;
		for(i = 0; i < NL; ++i){
			for (j = 0; j < NC; ++j){
				 dist = distEuclidienne(drawnVector, network[i][j].w,vectSize);
				 if(dist<tmp){
					if(sizeBMU>1){
						bmuTMP = freeList(bmuTMP);
						sizeBMU= 1;
						bmuTMP = (pos*) malloc(sizeBMU * sizeof(pos));
					}
					iBMU = 0;
				 	network[i][j].act = tmp = dist;
				 	bmuTMP->l = i;
				 	bmuTMP->c = j;
				 	bmuTMP->next = NULL;
				 }
                else if (dist == tmp){
					iBMU++;
			     	sizeBMU*=2;
				 	push(&bmuTMP,i,j);
				}
			}
		}
		bmu = randList(bmuTMP,iBMU);
		return bmu;
}

/**
* @method learning : Calcule le BMU, trouve son voisinnage et modifies la map avec l'apprentissage
* @param {iris *} dataBase: La base de donnée
* @param {neuron **} network: Map de neurones
* @param {double} alpha: l'alpha 
* @param {int} radius: le rayon de voisinnage
* @param {int} iriSize: Taille de la base de donnée
* @param {int} vectSize: Taille du vecteur de doubles
* @param {int} nbIt: Nombre d'itérations
*/
void learning(iris *dataBase,neuron **network, double alpha, int radius,int vectSize, int iriSize, int nbIt){
	int it,j,h,l,c;
	int *tInd = filler(iriSize);
	pos bmu;
	pos vois[2];
	double original_alpha = alpha;
	int original_radius = radius;
	iris drawnVector;
	for(it = 1; it <= nbIt; ++it){
		shuffle(tInd,iriSize);
		for(j = 0; j < iriSize;++j){
			drawnVector = dataBase[tInd[j]];
			bmu = BMU(drawnVector,network,4);
			vois[0].l = (bmu.l - radius > 0)? bmu.l - radius :0;
			vois[1].l = (bmu.l + radius >= NL)?  NL - 1:bmu.l + radius;
  			vois[0].c = (bmu.c - radius > 0)?  bmu.c - radius : 0;
   			vois[1].c = (bmu.c + radius >= NC)?  NC - 1: bmu.c + radius;


			for(l = vois[0].l; l <= vois[1].l ;++l){
				for(c = vois[0].c; c <= vois[1].c; ++c){
					for(h = 0; h < vectSize; ++h){
						network[l][c].w[h] +=  alpha * (drawnVector.v[h] - network[l][c].w[h]);
					}
				}
			}
		}
        alpha = original_alpha * (1.0-((double)it / (double)nbIt));
        radius = original_radius * (1.0 -((double)it/(double)nbIt));
	}

}

/**
* @method labellisation : Pour chaque neurone, trouve l'étiquette qui lui correspond par la distance Euclidienne
* @param {neuron **} network: Map de neurones
* @param {iris *} dataBase: La base de donnée
* @param {int} iriSize: Taille de la base de donnée
* @param {int} vectSize: Taille du vecteur de doubles
*/
void labellisation(neuron **network,iris *dataBase,int iriSize,int vectSize){
	int i,j,a,pos;
	double tmp,dist;
	
	for(i = 0; i < NL;++i){
		for(j = 0; j < NC; ++j){
			tmp = distEuclidienne(dataBase[0], network[0][0].w,vectSize);
			pos = 0;
			for(a = 0; a < iriSize; ++a){
				dist = distEuclidienne(dataBase[a], network[i][j].w,vectSize);

				if(dist<tmp){
					tmp = dist;
					pos = a;
				}
			}
			network[i][j].etq = dataBase[pos].name;
		}
	}
}

/**
* @method testing : Donne le nombre de réussite
* @param {neuron **} network: Map de neurones
* @param {iris *} dataBase: La base de donnée
* @param {int} iriSize: Taille de la base de donnée
* @param {int} vectSize: Taille du vecteur de doubles
*/
int testing(neuron **network, iris* dataBase, int iriSize,int vectSize){
    int i,point;
    pos bmu;
    bmu.l = bmu.c = point = 0;

    for(i= 0; i < iriSize; ++i){
        bmu = BMU(dataBase[i],network,vectSize);
        if (strcmp(dataBase[i].name, network[bmu.l][bmu.c].etq) == 0)
            point++;
    }
    return point;
}


/**
* @method affichage : Affiche la map de neuronne en différenciant les classes
* @param {neuron **} network: Map de neurones
* @param {iris *} dataBase: La base de donnée
*/
void affichage(neuron **network,iris *dataBase){
int i, j;

	for(i = 0 ; i < NL ; ++i){
		for(j = 0; j < NC;++j){

			if (strstr(network[i][j].etq, "setosa") != NULL){
				printf("%s 1 ",LCYAN);
			}

			if (strstr(network[i][j].etq, "versicolor") != NULL){
				printf("%s 2 ",LGREEN);
			}
			if (strstr(network[i][j].etq, "virginica")!= NULL){
				printf("%s 3 ",LMAGEN);
			}
            printf("%s", RESET);
		}
		printf("\n");
	}
		printf("\033[0;36mIris-setosa = 1 \n");
		printf("\033[0;32mIris-versicolor = 2 \n");
		printf("\033[0;35mIris-virginica = 3 \n");
		printf("%s", RESET);
}