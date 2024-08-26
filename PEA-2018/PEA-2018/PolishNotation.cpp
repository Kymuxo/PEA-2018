#pragma once

#include "stdafx.h"
#include "Output_functions.h"
#include "PolishNotation.h"



int PN::priority(char symbol)
{
	if (symbol == LEX_SUMM || symbol == LEX_DIFFERENCE)
		return 2;
	
	if (symbol == LEX_MULTIPLICATION || symbol == LEX_DIVISION)
		return 3;
	
	return 4;
}

void PN::copy_LT(LT::LexTable& lextable, LT::LexTable& lextable2, int i)
{
	lextable.table[i].lexema = lextable2.table[i].lexema;
	lextable.table[i].line_code = lextable2.table[i].line_code;
	lextable.table[i].number_in_id = lextable2.table[i].number_in_id;
	lextable.table[i].number_in_input = lextable2.table[i].number_in_input;
};

void PN::Polish_notation_inverse(int &start_position, LT::LexTable& lextable, IT::IdTable& idtable, IN in, LT::LexTable& lextable2)
{
	std::stack <int> buffer;
	int last_postion;
	
	for (last_postion = start_position; lextable.table[last_postion].lexema != LEX_SEMICOLON; last_postion++);
	vector<int>EXPRESSION;

	for (int i = start_position; i < last_postion; i++)
	{
		if (lextable.table[i].lexema == LEX_LEFT_BRACKET)
			buffer.push(i);
		
		if (lextable.table[i].lexema == LEX_RIGHT_BRACKET)
		{
			while (!buffer.empty() && lextable.table[buffer.top()].lexema != LEX_LEFT_BRACKET)
			{
				EXPRESSION.push_back(buffer.top());
				buffer.pop();
			}
			
			buffer.pop();
		}
		
		if (lextable.table[i].lexema == LEX_ID && lextable.table[i + 1].lexema == LEX_LEFT_BRACKET)
		{
			EXPRESSION.push_back(i);
			EXPRESSION.push_back(-1);
			i += 2;
			
			while (lextable.table[i].lexema != LEX_RIGHT_BRACKET && lextable.table[i - 1].lexema != LEX_RIGHT_BRACKET)
			{
				EXPRESSION.push_back(i);
				i += 2;
			}
			
			EXPRESSION.push_back(-2);
		}
		
		if (lextable.table[i].lexema == LEX_SIGN)
		{
			while (!buffer.empty() && PN::priority(in.text[lextable.table[i].number_in_input]) <= PN::priority(in.text[lextable.table[buffer.top()].number_in_input]) && 
				lextable.table[buffer.top()].lexema != LEX_LEFT_BRACKET)
			{
				EXPRESSION.push_back(buffer.top());
				buffer.pop();
			}
			
			buffer.push(i);
		}
		
		if (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
			EXPRESSION.push_back(i);
	}
	
	while (!buffer.empty())
	{
		if (lextable.table[buffer.top()].lexema != LEX_LEFT_BRACKET && lextable.table[buffer.top()].lexema != LEX_RIGHT_BRACKET) 
			EXPRESSION.push_back(buffer.top());
		
		buffer.pop();
	}
	
	for (unsigned int i = 0; i <EXPRESSION.size(); i++)
	{
		if (EXPRESSION[i] == -1)
		{
			lextable2.table[i + start_position].lexema = '[';
			lextable2.table[i + start_position].line_code = lextable2.table[i + start_position - 1].line_code;
			
			continue;
		}
		
		if (EXPRESSION[i] == -2)
		{
			lextable2.table[i + start_position].lexema = ']';
			lextable2.table[i + start_position].line_code = lextable2.table[i + start_position - 1].line_code;
			
			continue;
		}
		
		lextable2.table[i + start_position].lexema = lextable.table[EXPRESSION[i]].lexema;
		lextable2.table[i + start_position].line_code = lextable.table[EXPRESSION[i]].line_code;
		lextable2.table[i + start_position].number_in_id = lextable.table[EXPRESSION[i]].number_in_id;
		lextable2.table[i + start_position].number_in_input = lextable.table[EXPRESSION[i]].number_in_input;
	}

	lextable2.table[EXPRESSION.size() + start_position].lexema = LEX_SEMICOLON;
	lextable2.table[EXPRESSION.size() + start_position].line_code = lextable2.table[EXPRESSION.size() + start_position - 1].line_code;

	for (int i = EXPRESSION.size() + start_position + 1; i < last_postion + 1; i++)
	{
		lextable2.table[i].lexema = NULL;
		lextable2.table[i].line_code = lextable2.table[i - 1].line_code;
	}

	start_position = last_postion;
}

void PN::Polish_Notation_main(LT::LexTable& lextable, IT::IdTable& idtable, IN in, LOG log)
{
	LT::LexTable lextable2 = LT::Create(LT_MAXSIZE);
	IT::IdTable ID_Table2 = IT::Create(200);

	for (int i = 1; i < lextable.size; i++)
	{
		if (lextable.table[i - 2].lexema == LEX_ID && lextable.table[i - 1].lexema == '=')
		{
			int st = i;
			Polish_notation_inverse(i, lextable, idtable, in, lextable2);
			
			for (; st < i + 1; st++)
				copy_LT(lextable, lextable2, st);
		}
	}
	
	log.WriteLine("Таблица лексем после преобразования к обратной Польской записи\n", (*log.stream_for_log));
	OF::output_lexems(lextable, log, in);
}