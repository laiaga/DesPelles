#ifndef DPLL
#define DPLL

#include "utils.h"
#include "data_types.h"

/**
 * \brief Searches for an interpretation that satisfies F
 * \param F the cnf we want to satisfy
 * \parma I an interpretation (can be partially instantied) of F
 * \return 1 if a solution exists, 0 otherwise
 */
int satisfiable_first_solution(cnf * F, int I[]);

#endif // DPLL
