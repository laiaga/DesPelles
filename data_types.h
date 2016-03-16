#ifndef DATA_TYPES
#define DATA_TYPES

typedef int* interpretation;
typedef int literal;

typedef struct{
	int nb_lit;
	int nb_clauses;
	int** formule;
} *cnf;

#endif //DATA_TYPES