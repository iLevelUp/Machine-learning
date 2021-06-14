#ifndef _LEARNING
#define _LEARNING

void vecteurNeurone(neuron **network, iris vectMoyen, int vectSize, double vMin, double vMax);
double distEuclidienne(iris dataBase, double* vector, int vectSize);
pos BMU(iris drawnVector,neuron **network, int vectSize);
void learning(iris *dataBase,neuron **network, double alpha, int radius,int vectSize, int iriSize, int nbIt);
void labellisation(neuron **network,iris *dataBase,int iriSize,int vectSize);
void affichage(neuron **network, iris *dataBase);
int testing(neuron **network, iris* dataBase, int iriSize,int vectSize);
#endif