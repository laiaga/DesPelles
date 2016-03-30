#include "utils.h"


int is_empty(cnf F)
{
  return (F->f == NULL);
}


literal pure_or_mono(cnf F)
{
  int n = F->nb_lit;
  
  literal l,ret;
  int neg[n+1],pos[n+1],monoFound;//0 is not a recognized literal, hence the need to have n+1 length
  int i,size;
  formula form;
  clause tmp;
  monoFound = FALSE;
  i = 0;
  ret = 0;
  form=F->f;
  
  for(i=0 ; i<=n ; i++)
    {
      neg[i]=FALSE;//neg will allow to remember if we found a "FALSE" occurence of a literal
      pos[i]=FALSE;//pos will do the same with "TRUE"
    }

  while(form!=NULL && !monoFound)
    {
      size=0;//Incremented with each literal of a clause in order to know if we have a mono-literal
      tmp =form->c;
      
      while(tmp != NULL)
	{
	  if(tmp->lit > 0)
	    {
	      pos[tmp->lit] = TRUE;
	    }
	  else
	    {
	      neg[-(tmp->lit)] = TRUE;
	    }
	  size++;
	  tmp = tmp->next;
	}
      if(size==1)
	{
	  l = form->c->lit;
	  monoFound = TRUE;
	}
      form = form->next;
    }

  if(monoFound)
    {
      ret = l;
    }
  else
    {
      i=1;
      while(!ret && i<=n)
	{
	  if(pos[i] && !neg[i]) ret = i;
	  if(!pos[i] && neg[i]) ret = -i;
	  i++;
	}
    }

  return ret;
}


int contains_empty_clause(cnf F)
{
  int i=0,ret=FALSE;
  formula f = F->f;
  while(f!= NULL && !ret)
    {
      if(f->c == NULL)
	{
	  ret = TRUE;
	}
      f = f->next;
    }
  return ret;
}

void simplify(cnf F, interpretation I)
{
  clause pred,curr;
  int skip;
  formula form, parentForm;
  form = F->f;
  parentForm = form;
  
  while(form != NULL)
    {
      curr = form->c;
      pred = curr;
      skip = FALSE;
      
      while(curr != NULL && !skip)
	{
	  if(curr->lit > 0 && I[curr->lit] == TRUE)
	    {
	      parentForm->next = form->next;
	      free(form);
	      form = parentForm->next;
	      skip = TRUE;
	    }
	  else if(curr->lit < 0 && I[curr->lit] == FALSE)
	    {
	      parentForm->next = form->next;
	      free(form);
	      form = parentForm->next;
	      skip = TRUE;
	    }
	  
	  if(curr->lit > 0 && I[curr->lit] == TRUE)
	    {
	      pred->next = curr->next;
	      free(curr);
	      curr = pred;
	    }
	  else if(curr->lit < 0 && I[curr->lit] == FALSE)
	    {
	      pred->next = curr->next;
	      free(curr);
	      curr = pred;
	    }
	  
	  pred = curr;
	  curr = curr->next;
	}
      parentForm = form;
      form = form->next;
    }
}

literal random_lit(cnf F,interpretation I)
{
  int i=1,ret=0;
  while(i<=F->nb_lit && !ret)
    {
      if(I[i] == UNDEF) ret=i;
      i++;
    }
  return ret;
}

void copy(interpretation src, interpretation dest, int size)
{
  int i;
  for(i=0 ; i<size ; i++)
    {
      dest[i] = src[i];
    }
}
