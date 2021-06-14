#include "struct.h"
#ifndef _INITIALIZATION
#define _INITIALIZATION

int randint(int min, int max);
void normalization(iris *dataBase, int size, int nb);
void shuffle (int *tab, int size);
int *filler(int size);
iris vectMoyen(iris *dataBase, int iriSize, int vectSize);

#endif