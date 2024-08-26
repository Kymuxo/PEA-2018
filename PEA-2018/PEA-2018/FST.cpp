#include "stdafx.h"
#include "FST.h"



namespace FST
{
	RELATION::RELATION(char c, int ns)
	{
		symbol = c;
		nnode = ns;
	}

	NODE::NODE()
	{
		n_relation = 0;
		RELATION *relations = NULL;
	}

	NODE::NODE(int n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION *p = &rel;
		relations = new RELATION[n];
		for (int i = 0; i < n; i++)
		{
			relations[i] = *p;
			p++;
		}
	}

	Fst::Fst(char* s, enum_FST number1, char lexemp, int ns, NODE n, ...)
	{
		lexem_to_return = lexemp;
		string = s;
		number = number1;
		nstates = ns;
		nodes = new NODE[ns];
		NODE *p = &n;
		for (int k = 0; k < ns; k++)
		{
			nodes[k] = *p;
			p++;
		}
		rstates = new int[nstates];
		memset(rstates, 0xFF, sizeof(int)*nstates);												//-1
		rstates[0] = 0;
		position = -1;
	}

	bool step(Fst &fst, int *&rstates)
	{
		bool flag = false;
		std::swap(rstates, fst.rstates);
		for (int i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
			{
				for (int j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						flag = true;
					};
				};
			};
		};
		return flag;
	}

	bool execute(Fst &fst)																	//проверка на выполнение
	{
		int *rstates;
		rstates = new int[fst.nstates];
		memset(rstates, 0xFF, sizeof(int)*fst.nstates);										// -1 
		int lstring = fst.string.length();
		bool flag = true;
		for (int i = 0; (i < lstring) && flag; i++)
		{
			fst.position++;
			flag = step(fst, rstates);
		}
		delete[] rstates;
		if (fst.rstates[fst.nstates - 1] == lstring && fst.position == lstring - 1)
			return true;
		else
			return false;
		return flag;
	}

	void setFST(Fst& f, std::string newStr)
	{
		f.position = -1;
		f.string = newStr;
		f.rstates[0] = 0;
	}
}