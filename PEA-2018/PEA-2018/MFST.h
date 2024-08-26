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
	struct MfstState		//	Состояние НКА С МП	(MFST state)
	{
		int lenta_position;	//	текущая позиция на ленте по проходу ЛТ					(current position on tape)
		int nrulechain;		//	текущая попытка взятого правила цепочки					(current entered rule chain)
		int nrule;			//	текущая попытка взятого правила							(current entered rule)
		MFSTSTACK st;		//	таблица лексем в интовых значениях, по порядку хранятся	(LT in int values)
							//	construktors
		MfstState();
		MfstState(int pposition, MFSTSTACK pst, int pnrule, int pnrulechain);
	};
	
	struct Mfst	//	НКА С МП	(MFST)
	{
		int* lenta;				//	Лента состоящая из лексем	(tape, consist of lexems)
		int lenta_position;		//	Позиция на ленте			(position on tape)
		int nrule;				//	Номер правила				(number rule)
		int nrulechain;			//	Номер цепочки				(number rule chain)
		int lenta_size;			//	Размер ленты				(size of tape)
		GRB::Greibach grebach;	//	Грамматика					(grammatiks in Greibach form)
		LT::LexTable lex;		//	Таблица лексем				(lex table|LT)
		MFSTSTACK st;			//	лента с текущими интовыми значениями, номера цепочек	(tape with int values)
		std::stack<MfstState> storestate;	//	Стек, содержащий копии из структур MfstStare	(this stack consist of savestates-struct urs MFST state)

		enum RC_STEP {			// код возврата функции step											(code|flag return from function step)
			NS_OK,				// найдено правило и цепочка, цепочка записана в стек					(rule founded, chain added in stack)
			NS_NORULE,			// не найдено правило грамматики										(not found rule)
			NS_NORULECHAIN,		// не найдена подходящая цепочка правила								(not found rule chain)
			NS_ERROR,			// неизвестный нетерминальный символ грамматики							(not found rule to N(nonterminal))
			TS_OK,				// тек. символ ленты == вершине стека, продвинулась лента, pop стека	(current symbol=stack.top)
			TS_NOK,				// тек. символ ленты != вершине стек, восстановлено расстояние			(current symbol!=stack.top=>restate)
			LENTA_END,			// текущая позиция ленты >= lenta_size, конец ленты						(end of lenta)
			START				// неожиданно код возврата (ошибка в step) - начальное значение при проходе	(start value)
		};
		
		struct MfstDiagnosis					//	Хранение ошибок НКА С МП	(errors)
		{
			int lenta_position;					//	Позиция на ленте	(position on tape)
			RC_STEP rc_step;					//	код возврата что за состояние вызвало error (error flag)
			int nrule;	int nrule_chain;		//	выбранное правила и цепочка(entered rule and rule chain)
												//	construktors
			MfstDiagnosis();
			MfstDiagnosis(int plenta_position, RC_STEP prc_step, int pnrule, int pnrule_chain);
		}diagnosis[MFST_DIAGN_NUMBER];			//errors, size massiv is MFST_DIAGN_NUMBER
		
		void savediagnosis(RC_STEP pprc_step);	//	Сохранение состояния

		char* getCSt(char* buf);				//	translate from int to rule of char
		char* getCLenta(char* buf, int pos, int n = 25);
		char* getDiagnosis(int n, char* buf);

		void push_chain(GRB::Rule::Chain chain);//	Закинуть цепочку	(push chain)
		RC_STEP step();							//	Чек на проход шага		(check on run step)
		void start();							//	функция начала синтаксического анализа	(start syntactic analiz)

		struct Deducation						//	Дерево разбора	(parse tree)
		{
			int size;							// кол-во шагов в выводе		(numbers of steps in output)
			int* nrules;						// номера правил грамматики		(numbers rules of grammatiks)
			int* nrulechains;					// номера цепочек правил грамматики (numbers rules chains of grammatiks)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		}deducation;							//	element parse tree

		void savededucation();					//	сохранить дерево разбора	(save parse tree) 
		void printrules();						//	Вывод дерева разбора		(output parse tree)
		void saveState();						//	Сохранить состояние	(save state)
		bool reststate();						//	Откат состояния		(return past state)
												//construktors
		Mfst(LT::LexTable plex, GRB::Greibach pgrebach, std::ofstream& buff);

	};
}