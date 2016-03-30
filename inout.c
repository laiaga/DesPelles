#include "inout.h"

void read(char * filename,  cnf * F)
{
  FILE * file = fopen(filename,"r");
  if(file)
    {
      int tmp;
      char* buffer;
      char res[10];
      regex_t regex;
      ssize_t read;
      size_t len=0;
      
      regcomp(&regex,"^[-?[:digit:]+]",0);
      
      (*F) = (cnf)malloc(sizeof(struct _cnf));

      (*F)->nb_lit = tmp;
      
      while (read=getline(&buffer,&len,file) != -1)
	{
	  regexec(&regex, buffer, 10, &res, 0);
	  printf("%s\n",buffer);
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

void keyboard_cnf(cnf * F)
{
  int n,m,p,i,j;
  literal l;
  formula form = NULL;
  clause c = NULL, tmp = NULL;
  (*F) = (cnf)malloc(sizeof(struct _cnf));
  
  printf("How many literals in the formula : ");
  scanf("%d",&n);
  
  if((*F)==NULL)
    {
      perror("Unable to allocate memory in keyboard_cnf : abort.");
      return;
    }
  (*F)->nb_lit = n;
  (*F)->f = form;

  printf("How many clauses in the formula : ");
  scanf("%d",&m);

  for(i=0 ; i<m ; i++)
    {
      form = (formula)malloc(sizeof(struct _formula));
      form->c = NULL;
      printf("\tHow many literals in the %dth clause : ",i+1);
      scanf("%d",&p);

      printf("\tInput each literal separated by pressing enter (or 0 to exit).\n");
      for(j=0 ; j<p ; j++)
	{
	  scanf("\t\t%d",&l);
	  if(l>n || l<-n)
	    {
	      printf("WARNING : You must input a literal between %d and %d (0 exits the program).\n",-n,n);
	      j--;
	    }
	  else if(l==0)
	    {
	      printf("Manuel exit.\n");
	      return;
	    }
	  else
	    {
	      tmp = (clause)malloc(sizeof(struct node));
	      tmp->lit = l;
	      if(form->c == NULL) form->c = tmp;
	      else c->next = tmp;
	      c = tmp;
	    }
	}
      form = form->next;
    }
}
