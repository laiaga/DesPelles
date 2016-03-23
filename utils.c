int empty(cnf F)
{
	return F->nb_clauses == 0;
}

int pur_ou_mono(cnf F, interpretation I, int* signe)
{
	int n = F->nb_lit, i;
	int[n] tmp;
	for(i=0 ; i<n ; i++)
	{
		tmp = 0;
	}
	for(i=0 ; i<n ; i++)
	{
		for(j=0 ; j<n ; j++)
		{
			if(F->clauses[i][j]
		}
	}
}

int contains_empty_clause(cnf F, interpretation I)
{
	int i=0,j=0,valid=0,ret=1;
	int* clause;
	while(i<F->nb_clauses && ret)
	{
		clause = F->formule[i];
		while(j<nb_lit && !valid)
		{
			if((I[j]==1 && clause[j]==1) || (I[j]==-1 && clause[j]==-1))
			{
				valid=1;//la clause est validée car un de ses littéraux est à vrai
			}
			else if(I[j]=0 && clause[j]!=0)
			{
				valid=1;//la clause est validée car un de ses littéraux est non-instancié
			}
			j++;
		}
		if(j==nb_lit)ret=0;
		i++;
	}
	return ret;
}
