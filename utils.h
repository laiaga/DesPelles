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
int is_empty(cnf * F);

/**
 * \brief Searchs a cnf in order to find mono- or pure-literals
 * \param F the cnf to be searched
 * \param I the interpretation of the cnf in order to know if the literal is
 * already instantied
 * \return 0 if no such literal was found, the signed literal otherwise
 */
int pure_or_mono(cnf * F, int I[]);

/**
 * \brief Checks if a cnf contains an empty clause (and thus is unsolvable)
 * \param F the cnf to be checkedP
 * \return true if there is an empty clause, FALSE otherwise
 */
int contains_empty_clause(cnf * F);

/**
 * \brief Simplifies a cnf according to an interpretation I of its literals
 * \param F the cnf to be simplified
 * \param I the interpretation
 */
void simplify(cnf * F, int I[]);

/**
 * \brief Selects a random non-yet instanciated int
 * \param F the cnf to be searched
 * \param I the interpretation of F
 * \return the index of the first acceptable int found
 */
int random_lit(cnf * F, int I[]);

/**
 * \brief Copies a cnf into another
 * \param src the cnf to be copied
 * \param dest the empty cnf to be filled 
 */
void copy(cnf * src, cnf * dest);

/**
 * \brief Displays the formula on screen
 * \param F the formula to be dispayed
 */
void display(cnf * F);

/**
 * \brief Displays an interpretation of a formula
 * \param I the interpretation to be displayed
 * \param n the number of ints
 */
void display_interpretation(int I[], int n);

/**
 * \brief Converts a char to the corresponding int (only for 1 to 9)
 * \param c the char to convert
 * \return the integer value of c
 */
int char_to_int(char c);

/**
 * \brief Processes a cnf and frees all of its components, then frees the cnf itself
 * \param F the cnf to be freed
 */
void free_cnf(cnf ** F);

#endif // UTILS
