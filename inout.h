#ifndef INOUT
#define INOUT

#include "utils.h"
#include "data_types.h"

/**
 * \brief reads a cnf from a file
 * \param filename the path to the file to be read
 * \param F the cnf to be instantied
 *
 * The file has to be as follows :
 * n
 * a -b
 * where n is the number of literals (here 2) and a and b are literals (you have to use numbers)
 * - means "not", and you can create as much clauses as you want
 * you can only use numbers from 1 to 9 as literals
 */
void read(char *filename, cnf ** F);

#endif // INOUT
