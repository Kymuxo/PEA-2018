#include "stdafx.h"
#include "GRB.h"
#include <cstdarg>



#define GRB_MAXRULE_CH	 25


namespace GRB
{
	//	���������� �������
	Greibach greibach(
		NS('S'), TS('$'), 6,												//	��������� ������, ��� �����, ���������� ������
		
		Rule(
			NS('S'), 600, 3,												//	�������� ��������� ���������		
			Rule::Chain(10, TS('f'), TS('i'), TS('('), NS('P'), TS(')'), TS('{'), NS('B'), NS('G'), TS('}'), NS('S')),
			Rule::Chain(4, TS('b'), TS('{'), NS('B'), TS('}')),
			Rule::Chain(19, TS('s'), TS('i'), TS('('), NS('P'), TS(')'), TS(';'), TS('s'), TS('i'), TS('('), NS('P'), TS(')'), TS(';'), TS('s'), TS('i'), TS('('), NS('P'), TS(')'), TS(';'), NS('S'))
			),
		
		Rule(
			NS('B'), 601, 10,												//	��������	
			Rule::Chain(3, TS('x'), TS('i'), TS(';')),
			Rule::Chain(4, TS('x'), TS('i'), TS(';'), NS('B')),
			Rule::Chain(5, TS('i'), TS('='), NS('V'), TS(';'), NS('B')),
			Rule::Chain(4, TS('i'), TS('='), NS('V'), TS(';')),
			Rule::Chain(4, TS('o'), TS('i'), TS(';'), NS('B')),
			Rule::Chain(3, TS('o'), TS('i'), TS(';')),
			Rule::Chain(3, TS('o'), TS('l'), TS(';')),
			Rule::Chain(4, TS('o'), TS('l'), TS(';'), NS('B')),
			Rule::Chain(2, TS('o'), TS(';')),
			Rule::Chain(3, TS('o'), TS(';'), NS('B'))
			),
		
		Rule(
			NS('G'), 605, 1,												//	������� ��������
			Rule::Chain(3, TS('r'), TS('i'), TS(';'))
			),
		
		Rule(
			NS('P'), 602, 2,												//	��������
			Rule::Chain(4, TS('p'), TS('i'), TS(','), NS('P')),
			Rule::Chain(2, TS('p'), TS('i'))
			),
		
		Rule(
			NS('V'), 603, 8,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS('v'), NS('V')),
			Rule::Chain(3, TS('l'), TS('v'), NS('V')),
			Rule::Chain(3, TS('('), NS('V'), TS(')')),
			Rule::Chain(5, TS('('), NS('V'), TS(')'), TS('v'), NS('V')),
			Rule::Chain(4, TS('i'), TS('('), NS('A'), TS(')')),
			Rule::Chain(6, TS('i'), TS('('), NS('A'), TS(')'), TS('v'), NS('V'))
			),
		
		Rule(
			NS('A'), 604, 4,												//	��������
			Rule::Chain(3, TS('i'), TS(','), NS('A')),
			Rule::Chain(3, TS('l'), TS(','), NS('A')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l'))
			)
					);


	//	������� (Chain)
	Rule::Chain::Chain() : size(0), nt(0) { };
	
	Rule::Chain::Chain(int psize, int s, ...)								//	���������� �������
	{
		nt = new int[size = psize];
		int* p = (int*)&s;
		
		for (int i = 0; i < psize; i++)	
			nt[i] = (int)p[i];
	};
	
	char* Rule::Chain::getCChain(char* b)									//	������� �� ������� ��������(int) � �������(char)
	{
		for (int i = 0; i < size; i++)	
			b[i] = alphabet_to_char(nt[i]);
		
		b[size] = NULL;
		
		return b;
	};
	
	char Rule::Chain::alphabet_to_char(int s)								//	������� ������� �� ������ ���
	{
		return (s>0) ? char(s) : char(-s);
	};
	
	//	������� (Rule)
	Rule::Rule() : nn(0x00), size(0) {	};
	
	Rule::Rule(int pnn, int piderror, int psize, Chain c, ...)				//	����������� ������
	{
		nn = pnn;
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain*p = &c;
		
		for (int i = 0; i < size; i++)
			chains[i] = p[i];
	};
	
	char* Rule::getCRule(char* b, int nchain)								// �������� �������  � ���� N->������� (��� ������(������))
	{
		char* bn = new char[GRB_MAXRULE_CH];								// GRB_MAXRULE_CH - ������������ ����� ������� � ������ � ������ �������
		bn[0] = Chain::alphabet_to_char(nn);	
		bn[1] = '-';	
		bn[2] = '>';	
		bn[3] = 0x00;
		strcat(bn, chains[nchain].getCChain(b));							//	� ������ ������ �������� ������
		
		return bn;
	};
	
	int Rule::getNextChain(int t, Rule::Chain& pchain, int j)				//	��������� ��������� ������� (���� ������� �� �����������)
	{
		for (; j < size; j++)
			if (chains[j].nt[0] == t)
			{
				pchain = chains[j];
				return j;
			}
		
		return -1;
	};
	
	//	������� (Gribach)
	Greibach::Greibach() : size(0), startN(0), stbottomT(0), rules(0) {};
	
	Greibach::Greibach(int pstartN, int pstbottom, int psize, Rule r, ...)	//	����������� ���������� (��������� �� �������� ������)
	{
		startN = pstartN;
		stbottomT = pstbottom;
		rules = new Rule[size = psize];
		Rule* p = &r;
		
		for (int i = 0; i < size; i++) 
			rules[i] = p[i];
	};
	
	int Greibach::getRule(int pnn, Rule& prule)								//	�������� ����� �������
	{
		int rulenum = -1;
		
		for (int i = 0; i < size; i++)
		{
			if (rules[i].nn == pnn)
			{
				prule = rules[rulenum = i];
				break;
			};
		};
		
		return rulenum;
	};
	
	Rule Greibach::getRule(int n)											//	�������� ������� �� ��������� ������ (���� ����� �� � �������, �� ������ ���������)
	{
		return n < size ? rules[n] : Rule();
	};
	
	Greibach getGreibach()													//	�������� ���������� �������	
	{
		return greibach;
	};
};
