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
 * \param I the interpretation of the cnf in order to know if the literal is
 * already instantied
 * \return 0 if no such literal was found, the signed literal otherwise
 */
literal pure_or_mono(cnf F, interpretation I);

/**
 * \brief Checks if a cnf contains an empty clause (and thus is unsolvable)
 * \param F the cnf to be checkedP
 * \return true if there is an empty clause, FALSE otherwise
 */
int contains_empty_clause(cnf F);

/**
 * \brief Simplifies a cnf according to an interpretation I of its literals
 * \param F the cnf to be simplified
 * \param I the interpretation
 */
void simplify(cnf F, interpretation I);

/**
 * \brief Selects a random non-yet instanciated literal
 * \param F the cnf to be searched
 * \param I the interpretation of F
 * \return the index of the first acceptable literal found
 */
literal random_lit(cnf F, interpretation I);

void copy(cnf src, cnf dest);

/**
 * \brief Displays the formula on screen
 * \param F the formula to be dispayed
 */
void display(cnf F);

/**
 * \brief Displays an interpretation of a formula
 * \param I the interpretation to be displayed
 * \param n the number of literals
 */
void display_interpretation(interpretation I, int n);

int char_to_int(char c);

#endif // UTILS
