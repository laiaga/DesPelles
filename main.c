#include "dpll.h"
#include "inout.h"
#include "data_types.h"
#include "utils.h"

//you have to specify the name of the file containing the cnf as the main's first argument 
int main(int argc, char **argv) {
  if(argc < 2)
    {
      perror("You have to specify a path to a file in argument.");
      return -1;
    }

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

  free_cnf(&F);
  return 0;
}
