#pragma once

#include <iostream>



#define NS(n) -int(n)
#define TS(n) int(n)


namespace GRB
{
	struct Rule
	{
		int nn;																//	нетерминал
		int iderror;														//	ошибка
		int size;															//	размер правила
		
		struct Chain														//	1 правило для нетерминала 
		{
			int size;														//	размер правила
			int* nt;														//	int значения для этого правила
																			//	конструктры
			Chain();
			Chain(int psize, int s, ...);

			char*getCChain(char *b);										//	перевод ветки правила из int в char
																			//	добавление символов в массив b
			static char alphabet_to_char(int s);							//	перевод 1 символа из int в char
		}*chains;															//	ветка правила
																			//	конструкторы
		Rule();
		Rule(int pnn, int piderror, int psize, Chain c, ...);
		
		char *getCRule(char*b, int nchain);									//	вывод дерева правил
		int getNextChain(int t, Rule::Chain&pchain, int j);
	};

	struct Greibach
	{
		int size; int startN; int stbottomT;
		Rule* rules;

		Greibach();
		Greibach(int pstartN, int pstbottomT, int psize, Rule r, ...);
		
		int getRule(int pnn, Rule &prule);									//	получить номер правила
		Rule getRule(int n);												//	получить правило по номеру
	};

	Greibach getGreibach();
}