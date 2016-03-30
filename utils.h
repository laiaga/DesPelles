#ifndef UTILS
#define UTILS

#include <stdlib.h>
#include <stdio.h>
#include "data_types.h"

/**
 * \brief Checks if a cnf is empty (and thus is satisfied)
 * \param F the cnf to be searched
 * \return TRUE if the cnf is empty, FALSE otherwise
 */
int is_empty(cnf F);

/**
 * \brief Searchs a cnf in order to find mono- or pure-literals
 * \param F the cnf to be searched
 * \return 0 if no such literal was found, the signed literal otherwise
 */
literal pure_or_mono(cnf F);

/**
 * \brief Checks if a cnf contains an empty clause (and thus is unsolvable)
 * \param F the cnf to be checked
 * \return true if there is an empty clause, FALSE otherwise
 */
int contains_empty_clause(cnf F);

/**
 * \brief Simplifies a cnf according to an interpretation I of its literals
 * \param F the cnf to be simplified
 * \param I the interpretation
 */
void simplify(cnf F,interpretation I);

/**
 * \brief Selects a random non-yet instanciated literal 
 * \param F the cnf to be searched 
 * \param I the interpretation of F
 * \return the index of the first acceptable literal found
 */
literal random_lit(cnf F,interpretation I);

/**
 * \brief Copies an interpretation
 * \param src the source of the copy
 * \param dest the destination of the copy
 * \param size the size of each interpretation (must be the same for the two)
 */
void copy(interpretation src,interpretation dest, int size);

#endif //UTILS
