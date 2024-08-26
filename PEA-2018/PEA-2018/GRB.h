#pragma once

#include <iostream>



#define NS(n) -int(n)
#define TS(n) int(n)


namespace GRB
{
	struct Rule
	{
		int nn;																//	����������
		int iderror;														//	������
		int size;															//	������ �������
		
		struct Chain														//	1 ������� ��� ����������� 
		{
			int size;														//	������ �������
			int* nt;														//	int �������� ��� ����� �������
																			//	�����������
			Chain();
			Chain(int psize, int s, ...);

			char*getCChain(char *b);										//	������� ����� ������� �� int � char
																			//	���������� �������� � ������ b
			static char alphabet_to_char(int s);							//	������� 1 ������� �� int � char
		}*chains;															//	����� �������
																			//	������������
		Rule();
		Rule(int pnn, int piderror, int psize, Chain c, ...);
		
		char *getCRule(char*b, int nchain);									//	����� ������ ������
		int getNextChain(int t, Rule::Chain&pchain, int j);
	};

	struct Greibach
	{
		int size; int startN; int stbottomT;
		Rule* rules;

		Greibach();
		Greibach(int pstartN, int pstbottomT, int psize, Rule r, ...);
		
		int getRule(int pnn, Rule &prule);									//	�������� ����� �������
		Rule getRule(int n);												//	�������� ������� �� ������
	};

	Greibach getGreibach();
}