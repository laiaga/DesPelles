#include "dpll.h"
#include "inout.h"
#include "data_types.h"

int main(int argc, char **argv) {
  cnf * F = NULL;
  read(argv[1], &F);
  display(F);

  int i;
  int I[F->nb_lit+1];
  for(i=0 ; i<F->nb_lit+1 ; i++)
  {
    I[i] = -1;
  }

  int ret = satisfiable_first_solution(F, I);
  if(!ret) printf("It seems there exists no solution :(\n");
  return 0;
}
