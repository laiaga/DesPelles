#ifndef INOUT
#define INOUT

#include "utils.h"
#include "data_types.h"

void read(char * filename, cnf * F);
void write(char * filename, cnf F);

/**
 * \brief Asks the user to input a cnf at the keyboard
 * \param F a pointer to an empty cnf to be initialized
 */
void keyboard_cnf(cnf * F);

#endif //INOUT
