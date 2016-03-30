#include "dpll.h"
#include "inout.h"
#include "data_types.h"

void create_cnf(cnf * F)
{
  *F = (cnf)malloc(sizeof(struct _cnf));
  (*F)->nb_lit = 2;
  (*F)->f = (formula)malloc(sizeof(struct _formula));
  (*F)->f->next = (formula)malloc(sizeof(struct _formula));
  (*F)->f->next->next = NULL;

  formula tmp = (*F)->f;
  clause c = (clause)malloc(sizeof(struct node));
  c->lit = 1;
  c->next = NULL;
  tmp->c = c;

  tmp = (*F)->f->next;
  c = (clause)malloc(sizeof(struct node));
  c->lit = -1;
  c->next = (clause)malloc(sizeof(struct node));
  c->next->lit=-2;
  c->next->next=NULL;
  tmp->c = c;  
}

int main(int argc, char** argv)
{
  cnf F=NULL;
  //keyboard_cnf(&F);
  create_cnf(&F);
  display(F);
  int I[F->nb_lit+1];
  I[0] = UNDEF;
  I[1] = UNDEF;
  I[2] = UNDEF;
  printf("%d\n",satisfiable_first_solution(F,I));
  int i;
  return 0;
}
