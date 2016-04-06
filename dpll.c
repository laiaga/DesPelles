#include "dpll.h"

int satisfiable_first_solution(cnf * F, int I[])
{
  if (is_empty(F)) 
    {
      printf("A solution has been found.\n");
      display_interpretation(I, F->nb_lit);
      return 1; // If the cnf is empty then it's satisfied
    }
  else if (contains_empty_clause(F))
    {
      return 0; // If the cnf contains an empty clause then it's unsatisfiable
    }
  else
    {
      int l = pure_or_mono(F, I);

      if (l != 0) // If there was a pure or mono-literal we set it to its  mandatory value
        {
          if (l > 0) {
            I[l] = 1;
          } else {
            I[-l] = 0;
          }
          simplify(F, I); // Then we make the according simplifications in the cnf...
          return satisfiable_first_solution(F, I); //... and check if our new cnf is satisfiable_first_solution
        }

      else
        {
          int l = random_lit(F, I); // Otherwise, we choose a random non-instanciated literal
          if(!l)
            {
              perror("You are asking for a non-instanciated literal but all are instanciated !");
              return 0;
            }

          int Ibis[F->nb_lit+1];
          int i;
          for(i=1 ; i<=F->nb_lit ; i++) Ibis[i] = I[i];
          I[l] = 1;
          Ibis[l] = 0;
          cnf * cp = malloc(sizeof(struct _cnf));
          copy(F,cp);;
          simplify(F, I);

          if (satisfiable_first_solution(F, I)) return 1;
          else
            {
              simplify(cp, Ibis);
              return satisfiable_first_solution(cp, Ibis);
            }
        }
    }
  return -1;
}
