#include "utils.h"

int is_empty(cnf * F) { return (F->f == NULL); }

int pure_or_mono(cnf * F, int I[])
{
  int n = F->nb_lit;
  int neg[n + 1], pos[n + 1], mono_found=0, i=0, l, ret=0,size;
  formula * f = F->f;
  clause * c;

  for (i = 0; i <= n; i++)
    {
      neg[i] = 0; // neg will allow to remember if we found a "0" occurence of a int
      pos[i] = 0; // pos will do the same with "1"
    }

  while (f != NULL && !mono_found)
    {
      size = 0; // Incremented with each int of a clause in order to know if we have a mono-int
      c = f->c;

      while (c != NULL)
        {
          if (c->lit > 0)
            {
              pos[c->lit] = 1;
            }
          else
            {
              neg[-(c->lit)] = 1;
            }
          size++;
          c = c->next;
        }
      if (size == 1)//if the clause we just went over was 1-literal long, then this is a mono-literal
        {
          l = f->c->lit;
          if(l>0 && I[l] == -1) mono_found = 1;//still have to check if he is not instantied yet
          if(l<0 && I[-l] == -1) mono_found = 1;
        }
      f = f->next;
    }

  if (mono_found)
    {
      ret = l;
    }
  else
    {
      i = 1;
      while (!ret && i <= n)//going through each literal of the cnf to check if one is pure (appeared only as pos or neg)
        {
          if (pos[i] && !neg[i] && I[i] == -1)
            ret = i;
          if (!pos[i] && neg[i] && I[i] == -1)
            ret = -i;
          i++;
        }
    }
  return ret;
}

int contains_empty_clause(cnf * F)
{
  int ret = 0;
  formula * f = F->f;
  while (f != NULL && !ret)
    {
      if (f->c == NULL)
        {
          ret = 1;
        }
      f = f->next;
    }
  return ret;
}

void simplify(cnf * F, int I[])
{
  clause * pred_c, * curr_c;
  int skip,b=0;
  formula * pred_f, * curr_f;
  curr_f = F->f;
  pred_f = curr_f;

  // Iterating through each clause of the formula
  while (curr_f != NULL)
    {
      curr_c = curr_f->c;
      pred_c = curr_c;
      skip = 0;
      while (curr_c != NULL && !skip)
        {
          b = 0;
          // If a literal appears as true and has benn interpreted as true
          if (curr_c->lit > 0 && I[curr_c->lit] == 1)
            {
              // We remove the current clause from the formula
              if (pred_f == curr_f)//if we were at the very begining, the processing is different
                {
                  F->f = curr_f->next;
                  free(curr_f);
                  curr_f = F->f;
                  pred_f = curr_f;
                }
              else
                {
                  pred_f->next = curr_f->next;
                  free(curr_f);
                  curr_f = pred_f->next;
                }
              skip = 1;
            }
          // Same goes with false
          if (curr_c->lit < 0 && I[-curr_c->lit] == 0)
            {
              if (pred_f == curr_f)
                {
                  F->f = curr_f->next;
                  free(curr_f);
                  curr_f = F->f;
                  pred_f = curr_f;
                }
              else
                {
                  pred_f->next = curr_f->next;
                  free(curr_f);
                  curr_f = pred_f->next;
                }
              skip = 1;
            }

          // However if a literal appears as true and is interpreted as false (or
          // the opposite)
          if (curr_c->lit > 0 && I[curr_c->lit] == 0)
            {
              // We remove it from the clause
              if(pred_c == curr_c)
                {
                  curr_c = curr_c->next;
                  free(pred_c);
                  curr_f->c = curr_c;
                  pred_c = curr_c;
                  b=1;
                }
              else
                {
                  pred_c->next = curr_c->next;
                  free(curr_c);
                  curr_c = pred_c->next;
                }
            }
          else if (curr_c->lit < 0 && I[-curr_c->lit] == 1)
            {
              if(pred_c == curr_c)
                {
                  curr_c = curr_c->next;
                  free(pred_c);
                  curr_f->c = curr_c;
                  pred_c = curr_c;
                  b=1;
                }
              else
                {
                  pred_c->next = curr_c->next;
                  free(curr_c);
                  curr_c = pred_c->next;
                }
            }

          pred_c = curr_c;
          if(!b) curr_c = curr_c->next;//in the case pred_c==curr_c, this code snipet has to be executed earlier 
        }
      
      if(!skip)//if a clause was satisfied, then we already went to the next clause, no need to do it again here
        {
          pred_f = curr_f;
          curr_f = curr_f->next;
        }
    }
}

int random_lit(cnf * F, int I[])
{
  int i = 1, ret = 0;
  while (i <= F->nb_lit && !ret)
    {
      if (I[i] == -1)
        ret = i;
      i++;
    }
  return ret;
}

void copy(cnf * src, cnf * dest) {
  if(src == NULL || dest == NULL)
    {
      perror("Trying to copy empty cnf");
      return;
    }

  dest->nb_lit = src->nb_lit;

  formula * src_f = src->f;
  formula * dest_f = malloc(sizeof(struct _formula));
  dest->f = dest_f;
  //copie de fdest->c = fsrc->c;
  if(src_f->c == NULL) dest_f->c = NULL;
  clause * src_c = src_f->c;
  clause * dest_c = malloc(sizeof(struct _clause));
  dest_f->c = dest_c;
  dest_c->lit = src_c->lit;
  clause * c = dest_c;
  src_c  = src_c->next;
  while(src_c != NULL)
    {
      c->next = malloc(sizeof(struct _clause));
      c = c->next;
      c->lit = src_c->lit;
      src_c = src_c->next;
    }
  c->next = NULL;

  formula * p = dest_f;
  src_f = src_f->next;
  while(src_f != NULL)
    {
      p->next = malloc(sizeof(struct _formula));
      p = p->next;
      //p->c = fsrc->c;
      if(src_f->c == NULL) p->c = NULL;
      src_c = src_f->c;
      dest_c = malloc(sizeof(struct _clause));
      p->c = dest_c;
      dest_c->lit = src_c->lit;
      c = dest_c;
      src_c = src_c->next;
      while(src_c != NULL)
        {
          c->next = malloc(sizeof(struct _clause));
          c = c->next;
          c->lit = src_c->lit;
          src_c = src_c->next;
        }
      c->next = NULL;
      src_f = src_f->next;
    }
  p->next = NULL;
}

void display(cnf * F)
{
  if (F == NULL)
    {
      perror("Trying to display an empty formula.");
      return;
    }
 
  formula * f;
  clause * c;
  f = F->f;

  printf("%d littéral/aux\n",F->nb_lit);

  while (f != NULL)
    {
      c = f->c;
      printf("(");
      while (c != NULL) 
        {
          printf("%d", c->lit);
          if (c->next != NULL) printf("|");
          c = c->next;
        }
      printf(")");
      if (f->next != NULL)
        printf("\n");
      
      f = f->next;
    }
  printf("\n");
}

void display_interpretation(int I[], int n) {
  int i;
  printf("[");
  for (i = 1; i < n; i++)
    {
      if (I[i] == 1)
        printf("T|");
      if (I[i] == 0)
        printf("F|");
      if (I[i] == -1)
        printf("_|");
    }
  if (I[i] == 1)
    printf("T]\n");
  if (I[i] == 0)
    printf("F]\n");
  if (I[i] == -1)
    printf("_]\n");
}

int char_to_int(char c)
{
  int ret = 0;
  if(c<49 || c>57)//i.e. if the number is between 1 and 9
    {
      perror("Trying to convert an unaccepted char to a number. You can convert only [1-9].\n");
    }
  else
    {
      ret = c-48;//48 is the ASCII code for 0
    }
  return ret;
}

void free_cnf(cnf ** F)
{
  formula * f = (*F)->f, * tmp_f = NULL;
  clause * c = NULL, * tmp_c = NULL;
  while(f != NULL)
    {
      c = f->c;
      while(c != NULL)
        {
          tmp_c = c;
          c = c->next;
          free(tmp_c);
        }

      tmp_f = f;
      f = f->next;
      free(tmp_f);
    }
  free(*F);
}
