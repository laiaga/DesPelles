#include "inout.h"

void read(char *filename, cnf *F) {
  FILE *file = fopen(filename, "r");
  if (file) {//check if the file opened correctly
    char tmp;
    int val;

    //allocation of the cnf
    (*F) = (cnf)malloc(sizeof(struct _cnf));

    //first we retrieve the number of literals, which is always the only number on the first line
    tmp = fgetc(file);
    val = char_to_int(tmp);
    (*F)->nb_lit = val;

    //reading the first \r\n
    tmp = fgetc(file);
    tmp = fgetc(file);

    formula  f=NULL;
    clause c=NULL;
    
    while(!feof(file))
    {
     
      if(f == NULL)//...except if f1 is NULL, which means this is the first loop cycle
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
        //then we chesck the value of tmp in order to know what to do 
        switch(tmp)
        {
          case '-'://if we read a -, it is necessarly followed by a number, that we negate
            tmp = fgetc(file);
            val = char_to_int(tmp)*(-1);

            if(c == NULL)
            {
              c = malloc(sizeof(struct node));
              c->next = NULL;
              f->c = c;
            }
            else
            {
              c->next = malloc(sizeof(struct node));
              c = c->next;
              c->next = NULL;
            }
            c->lit = val;
            break;
          case ' '://if it's a space, we skip it
            break;
          case '\r':
            break;
          default://otherwise, we add it to our clause
            val = char_to_int(tmp);

            if(c == NULL)
            {
              c = malloc(sizeof(struct node));
              c->next = NULL;
              f->c = c;
            }
            else
            {
              c->next = malloc(sizeof(struct node));
              c = c->next;
              c->next = NULL;
            }
            c->lit = val;
            break;
        }
      }
    }

    fclose(file);
  } else {
    perror("Unable to open file in function read.");
  }
}

void write(char *filename, cnf F) {
  FILE *file = fopen(filename, "w");
  if (file) {
    fprintf(file, "%d\n", F->nb_lit);
    formula form = F->f;
    while (form != NULL) {
      clause c = form->c;
      while (c != NULL) {
        fprintf(file, "%c ", c->lit);
        c = c->next;
      }
      form = form->next;
      fprintf(file, "\n");
    }

    fclose(file);
  }
}

void keyboard_cnf(cnf *F) {
  int n, m, p, i, j;
  literal l;
  formula form = NULL;
  clause c = NULL, tmp = NULL;
  (*F) = (cnf)malloc(sizeof(struct _cnf));

  printf("How many literals in the formula : ");
  scanf("%d", &n);

  if ((*F) == NULL) {
    perror("Unable to allocate memory in keyboard_cnf : abort.");
    return;
  }
  (*F)->nb_lit = n;
  (*F)->f = form;

  printf("How many clauses in the formula : ");
  scanf("%d", &m);

  for (i = 0; i < m; i++) {
    form = (formula)malloc(sizeof(struct _formula));
    form->c = NULL;
    printf("\tHow many literals in the %dth clause : ", i + 1);
    scanf("%d", &p);

    printf(
        "\tInput each literal separated by pressing enter (or 0 to exit).\n");
    for (j = 0; j < p; j++) {
      scanf("\t\t%d", &l);
      if (l > n || l < -n) {
        printf(
            "WARNING : You must input a literal between %d and %d (0 exits the "
            "program).\n",
            -n, n);
        j--;
      } else if (l == 0) {
        printf("Manuel exit.\n");
        return;
      } else {
        tmp = (clause)malloc(sizeof(struct node));
        tmp->lit = l;
        if (form->c == NULL)
          form->c = tmp;
        else
          c->next = tmp;
        c = tmp;
      }
    }
    form = form->next;
  }
}
