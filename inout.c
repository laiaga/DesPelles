#include "inout.h"

void read(char * filename, cnf ** F)
{
  FILE * file = fopen(filename, "r");

  if (file)//check if the file opened correctly
    {
      char tmp;
      int val;

      //allocation of the cnf
      (*F) = malloc(sizeof(struct _cnf));

      //first we retrieve the number of literals, which is always the only number on the first line
      tmp = fgetc(file);
      val = char_to_int(tmp);
      (*F)->nb_lit = val;

      //reading the first \n
      tmp = fgetc(file);

      formula * f=NULL;
      clause * c=NULL;

      while(!feof(file))
        {

          if(f == NULL)
            {
              f = malloc(sizeof(struct _formula));
              (*F)->f = f;
            }
          else
            {
              f->next = malloc(sizeof(struct _formula));
              f = f->next;
              f->next = NULL;
            }

          //reinitialize the clause
          c = NULL;

          //iterating until we reach end of line/file
          //reaching end of line means the clause is over
          while ((tmp = fgetc(file)) != '\n' && tmp != EOF)
            {
              //then we check the value of tmp in order to know what to do 
              switch(tmp)
                {
                case '-'://if we read a -, it is necessarly followed by a number, which we negate
                  tmp = fgetc(file);
                  val = char_to_int(tmp)*(-1);

                  if(c == NULL)
                    {
                      c = malloc(sizeof(struct _clause));
                      c->next = NULL;
                      f->c = c;
                    }
                  else
                    {
                      c->next = malloc(sizeof(struct _clause));
                      c = c->next;
                      c->next = NULL;
                    }
                  c->lit = val;
                  break;
                case ' '://if it's a space, we skip it
                  break;
                default://otherwise, we add it to our clause
                  val = char_to_int(tmp);

                  if(c == NULL)
                    {
                      c = malloc(sizeof(struct _clause));
                      c->next = NULL;
                      f->c = c;
                    }
                  else
                    {
                      c->next = malloc(sizeof(struct _clause));
                      c = c->next;
                      c->next = NULL;
                    }
                  c->lit = val;
                  break;
                }
            }
        }
    }
  else
    {
      perror("Unable to open file in function read.");
    }
}
