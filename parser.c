#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "initialization.h"
#include "struct.h"
#include "parser.h"
#include "learning.h"


/**
* @method takeLine : Récupère les lignes, les parse et insère dans une base de données
* @param {struct *} dataBase: La base de donnée ou sera stockée les données du fichier récupéré
* @param {char *} path: Le chemin du fichier
* @param {int} vectSize: La taille du vecteur de doubles
*/
void takeLine(iris *dataBase,char *path,int vectSize){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int k = 0;

    fp = fopen(path, "r");
    if(fp == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1) {
        parseLine(&dataBase[k],line,vectSize);
        k++;
    }
}

/**
* @method CountLines : Compte les lignes d'un fichier donné
* @param {char *} path: Le chemin du fichier
*/
int countLines(char *path) {
    FILE * fp;
    ssize_t read;
    size_t len = 0;
    char * line = NULL;
    int res = 0;

    fp = fopen(path, "r");
    if(fp == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1)
        res++;
    return res;
}

/**
* @method parseLine : Parse une ligne afin de récupérer ses doubles et son etiquette
* @param {struct *} irisData: La struct iris qui contiendra les données de la ligne parsée
* @param {char *} line: La ligne récupérée
* @param {int} vectSize: La taille du vecteur de doubles
*/
void parseLine(iris *irisData,char *line,int vectSize){
    int i = 0;
    char *strToken;
    char *endPtr;
    irisData->v = (double *)malloc(vectSize* sizeof(double));

    for(strToken = strtok(line,","); strToken != NULL; strToken = strtok(NULL,","), ++i){
    	if(i<vectSize){
    		double value = strtod(strToken,&endPtr);
    		irisData->v[i]= value;
        }
        else{
       		irisData->name = (char *)malloc(strlen(strToken));
       		strcpy(irisData->name,strToken);
        }
    }
}

/**
* @method takeDigit : Filtre la ligne en récupérant uniquement le nombre après '='
* @param {char *} line: La ligne récupérée
*/
char *takeDigit(char *line){ 
    int i=1;
    int j=0;
    int n=1;
    char *d; 
    char *number;
    number = malloc(n * sizeof(char));
    strtok(line,"="); 
    d = strchr(line,' '); 
    if(d[i] == ' ')
        i++;
    while(d[i] != '\0' && d[i] != '\n'){
        number[j++]=d[i++];
        if(j>=n){
          n++;
          number = realloc(number,n * sizeof(char));  
        }
    }
    number[j] ='\0';
    return number;
}

/**
* @method parseOption: Parse une ligne afin de récupérer ses options, elle utilise takeDigit
* @param {double []} option: Tableau dans lequel sera stocké les options
* @param {char *} line: La ligne récupérée
*/
void parseOption(double option[], char *line){
    int i = 0;
    char *strToken;
    char *endPtr;

    for(strToken = strtok(line,"="); strToken != NULL; strToken = strtok(NULL,"="), ++i){
        if((i%2)!=0){
            i-=1;
            option[i] = strtod(takeDigit(strToken),&endPtr);
        }
    }
}

/**
* @method takeOption : Récupère les options et les insère dans un tableau
* @param {char *} path: Le chemin du fichier
*/
void takeOption(double option[],char *path){
    FILE * fp;
    ssize_t read;
    size_t len = 0;
    char * line = NULL;
    int k = 0;

    fp = fopen(path, "r");
    if(fp == NULL)
        exit(EXIT_FAILURE);
    while((read = getline(&line, &len, fp)) != -1){
        parseOption(&option[k],line);
        k++;
    }
}