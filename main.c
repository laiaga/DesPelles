#include "dpll.h"
#include "inout.h"

int main(int argc, char** argv)
{
  cnf F=NULL;
  keyboard_cnf(F);
  display(F);
  return 0;
}
