#ifndef _LISTE
#define _LISTE

pos *addBMU(pos *bmu, int i, int j);
pos *addFrontBMU(pos *bmuL, int l, int c);
void push(pos** bmuL, int l, int c);
pos * freeList(pos * bmuL);
pos randList(pos *bmuL,int n);
void print_list(pos * bmuL);
#endif