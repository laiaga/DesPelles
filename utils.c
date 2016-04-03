#include "utils.h"

int is_empty(cnf F) { return (F->f == NULL); }

literal pure_or_mono(cnf F, interpretation I) {
  int n = F->nb_lit;

  literal l, ret;
  int neg[n + 1], pos[n + 1], monoFound; // 0 is not a recognized literal, hence
                                         // the need to have n+1 length
  int i, size;
  formula form;
  clause tmp;
  monoFound = FALSE;
  i = 0;
  ret = 0;
  form = F->f;

  for (i = 0; i <= n; i++) {
    neg[i] = FALSE; // neg will allow to remember if we found a "FALSE"
                    // occurence of a literal
    pos[i] = FALSE; // pos will do the same with "TRUE"
  }

  while (form != NULL && !monoFound) {
    size = 0; // Incremented with each literal of a clause in order to know if
              // we have a mono-literal
    tmp = form->c;

    while (tmp != NULL) {
      if (tmp->lit > 0) {
        pos[tmp->lit] = TRUE;
      } else {
        neg[-(tmp->lit)] = TRUE;
      }
      size++;
      tmp = tmp->next;
    }
    if (size == 1) {
      l = form->c->lit;
      if(l>0 && I[l] == UNDEF) monoFound = TRUE;
      if(l<0 && I[-l] == UNDEF) monoFound = TRUE;
    }
    form = form->next;
  }

  if (monoFound) {
    ret = l;
  } else {
    i = 1;
    while (!ret && i <= n) {
      if (pos[i] && !neg[i] && I[i] == UNDEF)
        ret = i;
      if (!pos[i] && neg[i] && I[i] == UNDEF)
        ret = -i;
      i++;
    }
  }
  return ret;
}

int contains_empty_clause(cnf F) {
  int i = 0, ret = FALSE;
  formula f = F->f;
  while (f != NULL && !ret) {
    if (f->c == NULL) {
      ret = TRUE;
    }
    f = f->next;
  }
  return ret;
}

void simplify(cnf F, interpretation I) {
  clause pred, curr;
  int skip,b=FALSE;
  formula form, parentForm;
  form = F->f;
  parentForm = form;

  // Iterating through each clause of the formula
  while (form != NULL) {
    curr = form->c;
    pred = curr;
    skip = FALSE;
    while (curr != NULL && !skip) {
      b = FALSE;
      // If a literal appears as true and has benn interpreted as true
      if (curr->lit > 0 && I[curr->lit] == TRUE) {
        // We remove the current clause from the formula
        if (parentForm == form) {
          F->f = form->next;
          free(form);
          form = F->f;
          parentForm = form;
        } else {
          parentForm->next = form->next;
          free(form);
          form = parentForm->next;
        }
        skip = TRUE;
      }
      // Same goes with false
      if (curr->lit < 0 && I[-curr->lit] == FALSE) {
        if (parentForm == form) {
          F->f = form->next;
          free(form);
          form = F->f;
          parentForm = form;
        } else {
          parentForm->next = form->next;
          free(form);
          form = parentForm->next;
        }
        skip = TRUE;
      }

      // However if a literal appears as true and is interpreted as false (or
      // the opposite)
      if (curr->lit > 0 && I[curr->lit] == FALSE) {
        // We remove it from the clause
        if(pred == curr)
        {
          curr = curr->next;
          //free(pred);
          form->c = curr;
          pred = curr;
          b=TRUE;
        }
        else
        {
          pred->next = curr->next;
          free(curr);
          pred = curr;
        }
      }
      else if (curr->lit < 0 && I[-curr->lit] == TRUE) {
        if(pred == curr)
        {
          curr = curr->next;
          free(pred);
          form->c = curr;
          pred = curr;
          b=TRUE;
        }
        else
        {
          pred->next = curr->next;
          free(curr);
          pred = curr;
        }
      }

      pred = curr;
      if(!b) curr = curr->next;
    }
    parentForm = form;
    if(!skip) form = form->next;
  }
}

literal random_lit(cnf F, interpretation I) {
  int i = 1, ret = 0;
  while (i <= F->nb_lit && !ret) {
    if (I[i] == UNDEF)
      ret = i;
    i++;
  }
  return ret;
}

void copy(cnf src, cnf dest) {
  if(src == NULL || dest == NULL)
  {
    perror("Trying to copy empty cnf");
    return;
  }

  dest->nb_lit = src->nb_lit;

  formula fsrc = src->f;

  formula fdest = malloc(sizeof(struct _formula));
  dest->f = fdest;
  //copie de fdest->c = fsrc->c;
  if(fsrc->c == NULL) fdest->c = NULL;
  clause csrc = fsrc->c;
  clause cdest = malloc(sizeof(struct node));
  fdest->c = cdest;
  cdest->lit = csrc->lit;
  clause c = cdest;
  csrc = csrc->next;
  while(csrc != NULL)
  {
    c->next = malloc(sizeof(struct node));
    c = c->next;
    c->lit = csrc->lit;
    csrc = csrc->next;
  }
  c->next = NULL;

  formula p = fdest;
  fsrc = fsrc->next;
  while(fsrc != NULL)
  {
    p->next = malloc(sizeof(struct _formula));
    p = p->next;
    //p->c = fsrc->c;
    if(fsrc->c == NULL) p->c = NULL;
    clause csrc = fsrc->c;
    clause cdest = malloc(sizeof(struct node));
    p->c = cdest;
    cdest->lit = csrc->lit;
    clause c = cdest;
    csrc = csrc->next;
    while(csrc != NULL)
    {
      c->next = malloc(sizeof(struct node));
      c = c->next;
      c->lit = csrc->lit;
      csrc = csrc->next;
    }
    c->next = NULL;
    fsrc = fsrc->next;
  }
  p->next = NULL;
}

void display(cnf F) {
  if (F == NULL) {
    perror("Trying to display an empty formula.");
    return;
  }

  formula f;
  clause c;
  f = F->f;

  printf("%d littéral/aux\n",F->nb_lit);

  while (f != NULL) {
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
      printf("\n^");

    f = f->next;
  }
  printf("\n");
}

void display_interpretation(interpretation I, int n) {
  int i;
  printf("[");
  for (i = 1; i < n; i++) {
    if (I[i] == TRUE)
      printf("T|");
    if (I[i] == FALSE)
      printf("F|");
    if (I[i] == UNDEF)
      printf("_|");
  }
  if (I[i] == TRUE)
    printf("T]\n");
  if (I[i] == FALSE)
    printf("F]\n");
  if (I[i] == UNDEF)
    printf("_]\n");
}

int char_to_int(char c)
{
  int ret = 0;
  if(c<49 || c>57)
  {
    perror("Trying to convert an unaccepted char to a number. You can convert only [1-9].\n");
  }
  else
  {
    ret = c-48;
  }
  return ret;
}