#ifndef DATA_TYPES
#define DATA_TYPES

typedef struct _clause
{
  int lit;
  struct node * next;
} clause;

typedef struct _formula
{
  clause * c;
  struct _formula * next;
} formula;

typedef struct _cnf
{
  int nb_lit;
  formula * f;
} cnf;

#endif // DATA_TYPES
