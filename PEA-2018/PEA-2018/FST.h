#pragma once

#include "stdafx.h"



namespace FST
{
	enum enum_FST
	{
		lex_NO_RESULT = 0,													//	Явная нумерация для простоты debug'а 
		lex_id = 1,
		lex_output = 2,
		lex_sign = 3,
		lex_varinteger = 4,
		lex_varstring = 5,
		lex_parinteger = 6,
		lex_parstring = 7,
		lex_funinteger = 8,
		lex_funstring = 9,
		lex_litinteger = 10,
		lex_begin = 11,
		lex_recovery = 12,
		lex_add_this = 13,
		lex_equally = 14,
		lex_stlinteger = 15,
		lex_stlstring = 16
	};

	struct RELATION															//	ребро
	{
		char symbol;
		int nnode;
		RELATION(char c = 0x00, int ns = NULL);
	};

	struct NODE																//	вершина
	{
		int n_relation;
		RELATION *relations;
		NODE();
		NODE(int n, RELATION rel, ...);
	};

	struct Fst																//	автомат
	{
		std::string string;
		enum_FST number;
		char lexem_to_return;
		int position;
		int nstates;
		NODE *nodes;
		int *rstates;
		Fst(char *s, enum_FST number1, char lexemp, int ns, NODE n, ...);
	};

	bool step(Fst &fst, int *&rstates);
	bool execute(Fst &fsts);
	void setFST(Fst &f, std::string newStr);
}