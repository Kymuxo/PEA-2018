#pragma once

#include <stack>
#include "GRB.h"
#include "LT.h"
#include <iostream>
#include <fstream>



#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 5


typedef std::stack<int> MFSTSTACK;

namespace MFST
{
	struct MfstState		//	��������� ��� � ��	(MFST state)
	{
		int lenta_position;	//	������� ������� �� ����� �� ������� ��					(current position on tape)
		int nrulechain;		//	������� ������� ������� ������� �������					(current entered rule chain)
		int nrule;			//	������� ������� ������� �������							(current entered rule)
		MFSTSTACK st;		//	������� ������ � ������� ���������, �� ������� ��������	(LT in int values)
							//	construktors
		MfstState();
		MfstState(int pposition, MFSTSTACK pst, int pnrule, int pnrulechain);
	};
	
	struct Mfst	//	��� � ��	(MFST)
	{
		int* lenta;				//	����� ��������� �� ������	(tape, consist of lexems)
		int lenta_position;		//	������� �� �����			(position on tape)
		int nrule;				//	����� �������				(number rule)
		int nrulechain;			//	����� �������				(number rule chain)
		int lenta_size;			//	������ �����				(size of tape)
		GRB::Greibach grebach;	//	����������					(grammatiks in Greibach form)
		LT::LexTable lex;		//	������� ������				(lex table|LT)
		MFSTSTACK st;			//	����� � �������� �������� ����������, ������ �������	(tape with int values)
		std::stack<MfstState> storestate;	//	����, ���������� ����� �� �������� MfstStare	(this stack consist of savestates-struct urs MFST state)

		enum RC_STEP {			// ��� �������� ������� step											(code|flag return from function step)
			NS_OK,				// ������� ������� � �������, ������� �������� � ����					(rule founded, chain added in stack)
			NS_NORULE,			// �� ������� ������� ����������										(not found rule)
			NS_NORULECHAIN,		// �� ������� ���������� ������� �������								(not found rule chain)
			NS_ERROR,			// ����������� �������������� ������ ����������							(not found rule to N(nonterminal))
			TS_OK,				// ���. ������ ����� == ������� �����, ������������ �����, pop �����	(current symbol=stack.top)
			TS_NOK,				// ���. ������ ����� != ������� ����, ������������� ����������			(current symbol!=stack.top=>restate)
			LENTA_END,			// ������� ������� ����� >= lenta_size, ����� �����						(end of lenta)
			START				// ���������� ��� �������� (������ � step) - ��������� �������� ��� �������	(start value)
		};
		
		struct MfstDiagnosis					//	�������� ������ ��� � ��	(errors)
		{
			int lenta_position;					//	������� �� �����	(position on tape)
			RC_STEP rc_step;					//	��� �������� ��� �� ��������� ������� error (error flag)
			int nrule;	int nrule_chain;		//	��������� ������� � �������(entered rule and rule chain)
												//	construktors
			MfstDiagnosis();
			MfstDiagnosis(int plenta_position, RC_STEP prc_step, int pnrule, int pnrule_chain);
		}diagnosis[MFST_DIAGN_NUMBER];			//errors, size massiv is MFST_DIAGN_NUMBER
		
		void savediagnosis(RC_STEP pprc_step);	//	���������� ���������

		char* getCSt(char* buf);				//	translate from int to rule of char
		char* getCLenta(char* buf, int pos, int n = 25);
		char* getDiagnosis(int n, char* buf);

		void push_chain(GRB::Rule::Chain chain);//	�������� �������	(push chain)
		RC_STEP step();							//	��� �� ������ ����		(check on run step)
		void start();							//	������� ������ ��������������� �������	(start syntactic analiz)

		struct Deducation						//	������ �������	(parse tree)
		{
			int size;							// ���-�� ����� � ������		(numbers of steps in output)
			int* nrules;						// ������ ������ ����������		(numbers rules of grammatiks)
			int* nrulechains;					// ������ ������� ������ ���������� (numbers rules chains of grammatiks)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		}deducation;							//	element parse tree

		void savededucation();					//	��������� ������ �������	(save parse tree) 
		void printrules();						//	����� ������ �������		(output parse tree)
		void saveState();						//	��������� ���������	(save state)
		bool reststate();						//	����� ���������		(return past state)
												//construktors
		Mfst(LT::LexTable plex, GRB::Greibach pgrebach, std::ofstream& buff);

	};
}