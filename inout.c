#include "inout.h"

void read(char * filename,  cnf F)
{
  FILE * file = fopen(filename,"r");
  if(file)
    {
      int tmp;
      
      F = (cnf)malloc(sizeof(struct _cnf));

      fscanf(file,"%d",&tmp);
      F->nb_lit = tmp;
      while (!feof (file))
	{  
	  tmp = fgetc(file);
	  //if(tmp == '\n')printf("test");
	  printf("%c|",tmp);
	  if(tmp > 0)
	    {
	    }
	  else
	    {
	    }
	}
      
      fclose(file);
    }
}

void write(char * filename, cnf F)
{
  FILE * file = fopen(filename, "w");
  if(file)
    {
      fprintf(file,"%d\n",F->nb_lit);
      formula form = F->f;
      while(form != NULL)
	{
	  clause c = form->c;
	  while(c != NULL)
	    {
	      fprintf(file,"%c ",c->lit);
	      c = c->next;
	    }
	  form = form->next;
	  fprintf(file,"\n");
	}
      
      fclose(file);
    }
}
