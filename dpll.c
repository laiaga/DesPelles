#include "dpll.h"

int satisfiable_first_solution(cnf F, interpretation I) {
  if (is_empty(F)) {
    printf("A solution has been found.\n");
    display_interpretation(I, F->nb_lit);
    return TRUE; // If the cnf is empty then it's satisfied
  } else if (contains_empty_clause(F)) {
    return FALSE; // If the cnf contains an empty clause then it's
                  // unsatisfiable_first_solution
  } else {
    literal l = pure_or_mono(F, I);
    if (l != 0) // If there was a pure or mono-literal we set it to its
                // mandatory value
    {
      if (l > 0) {
        I[l] = TRUE;
      } else {
        I[-l] = FALSE;
      }
      simplify(F, I); // Then we make the according simplifications in the
                      // cnf...
      return satisfiable_first_solution(
          F, I); //... and check if our new cnf is satisfiable_first_solution
    }

    else {
      literal l = random_lit(
          F, I); // Otherwise, we choose a random non-instanciated literal
      literal Ibis[F->nb_lit];
      copy(I, Ibis, F->nb_lit);
      I[l] = TRUE;

      if (satisfiable_first_solution(F, I))
        return TRUE;
      else {
        I[l] = FALSE;
        return satisfiable_first_solution(F, I);
      }
    }
  }
}
