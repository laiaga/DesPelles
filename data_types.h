#ifndef DATA_TYPES
#define DATA_TYPES

#define TRUE 1
#define FALSE 0
#define UNDEF -1

typedef int literal;

typedef int * interpretation;

typedef struct node {
  literal lit;
  struct node * next;
} * clause;

typedef struct _formula{
  clause c;
  struct _formula * next;
} * formula;

typedef struct _cnf{
  int nb_lit;
  formula f;
} * cnf;

#endif //DATA_TYPES
