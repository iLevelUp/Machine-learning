/**
* Nom : LOKO
* Prénom : Loïc
* Numéro étudiant : 15607684
* mail : lloicloko@gmail.com
*/

/** Comme mentionner dans l'erreur d'usage,
- Pour compiler : make
- Exécuter : ./iris iris_data.txt options.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "parser.h"
#include "initialization.h"
#include "learning.h"
#include "math.h"
#include "struct.h"


int main(int argc, char *argv[]) {
  
  if(argc < 3 || argc > 3) {
      fprintf(stderr, "Usage: ./iris iris_data.txt options.txt .\n");
      exit(0);
  }

  	srand(time(NULL));
    int i,j;
  	int iriSize = countLines(argv[1]);
    int nbOption = countLines(argv[2]);
    double option[nbOption];
    takeOption(option,argv[2]);
    int radius = option[0];
    int radiuSnd = option[1];
    int vectSize = option[2];
   	int nbIt = option[3];
   	int nbItSnd = option[4];
   	double alpha = option[5];
	  double alphaSnd = option[6];
    double vMin = option[7];
    double vMax = option[8];
    int point;
	  float resultat;
  	iris vectMoy;
	  iris *dataBase = (iris *)malloc(iriSize * sizeof(*dataBase));
  
  	neuron **neural_network = (neuron**)malloc(NL *sizeof(neuron*));
          for (i = 0; i < NL; ++i){
              neural_network[i] = (neuron*)malloc(NC * sizeof(neuron));
              for (j = 0; j < NC; ++j){
                  neural_network[i][j].w = (double*)malloc(vectSize * sizeof(double));
              }
          }

  	takeLine(dataBase,argv[1],vectSize);
  	normalization(dataBase,iriSize,vectSize);
  	vectMoy= vectMoyen(dataBase,iriSize,vectSize);
   	vecteurNeurone(neural_network,vectMoy,vectSize,vMin,vMax);
   	learning(dataBase,neural_network,alpha,radius,vectSize,iriSize,nbIt);
   	learning(dataBase,neural_network,alphaSnd,radiuSnd,vectSize,iriSize,nbItSnd);
   	labellisation(neural_network,dataBase,iriSize,vectSize);
   	affichage(neural_network,dataBase);
 	  point = testing(neural_network,dataBase,iriSize, vectSize);
    resultat = (((float)point*100)/(float)iriSize);
    printf("Nous avons un pourcentage de %.2f\n", resultat);

  
    free(dataBase); 
    free(neural_network); 	
}
