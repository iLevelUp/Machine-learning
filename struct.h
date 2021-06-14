#ifndef _STRUCT
#define _STRUCT
#define NL 10
#define NC 6
#define LCYAN  "\x1B[46m"
#define LGREEN  "\x1B[42m"
#define LMAGEN  "\x1B[45m"
#define RESET  "\x1B[0m"

struct iris{
	double *v;
	char *name;
	double norme;
};
typedef struct iris iris;

struct neuron{
	double *w;
	char *etq;
	double act;
};
typedef struct neuron neuron;

struct position{
	int l;
	int c;
	struct position *next;
};
typedef struct position pos;
#endif