#include "struct.h"
#ifndef _PARSER
#define _PARSER

void takeLine(iris *dataBase,char *path,int vectSize);
void parseLine(iris *irisData,char *line,int vectSize);
int countLines(char *path);
void parseOption(double option[], char *line);
void takeOption(double option[],char *path);
#endif