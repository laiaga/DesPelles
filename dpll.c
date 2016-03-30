#include "dpll.h"

int satisfiable(cnf F, interpretation I)
{
  if(is_empty(F))
    {
      return TRUE;//If the cnf is empty then it's satisfied
    }
  else if(contains_empty_clause(F))
    {
      return FALSE;//If the cnf contains an empty clause then it's unsatisfiable
    }
  else
    {
      literal l = pure_or_mono(F);
      if(l != 0)//If there was a pure or mono-literal we set it to its mandatory value
	{
	  if(l > 0)
	    {
	      I[l] = TRUE;
	    }
	  else
	    {
	      I[-l] = FALSE;
	    }
	  simplify(F,I);//Then we make the according simplifications in the cnf...
	  return satisfiable(F,I);//... and check if our new cnf is satisfiable
	}
      
      else
	{
	  literal l = random_lit(F,I);//Otherwise, we choose a random non-instanciated literal 
	  literal Ibis[F->nb_lit];
	  copy(I,Ibis,F->nb_lit);
	  I[l] = TRUE;
	  Ibis[l] = FALSE;

	  return (satisfiable(F,I) || satisfiable(F,Ibis));
	}
    }
}
