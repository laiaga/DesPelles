#include "dpll.h"

void satisfiable(cnf F, interpretation I)
{
	if(empty(F))
	{
		return 1;
	}
	else if(contains_empty_clause(F,I))
	{
		return 0;
	}
	else
	{
		int signe;
		literal l = pur_ou_mono(F,I,&signe);
		if(l != -1)
		{
			I[l] = signe;
			simplifier(F,I);
			if(satisfiable(F,I))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			litteral l = random_lit(F,I);
			I[l] = 1;
			cnf tmp;
			copie(F,tmp);
			simplifier(F,I);
			if(satisfiable(F,I))
			{
				return 1;
			}
			else
			{
				I[l] = -1;
				simplifier(tmp,I);
				if(satisfiable(tmp,I))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}

	}
}
