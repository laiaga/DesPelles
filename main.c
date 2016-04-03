#include "dpll.h"
#include "inout.h"
#include "data_types.h"

void create_cnf(cnf *F) {
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
  c->next->lit = -2;
  c->next->next = NULL;
  tmp->c = c;
}

int main(int argc, char **argv) {
  cnf F = NULL;
  read(argv[1], &F);
  //printf("%d\n",F->f->next->c->lit);
  display(F);
  return 0;
}
