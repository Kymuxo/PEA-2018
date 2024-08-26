#pragma once

#include "FST.h"
#include "stdafx.h"
#include "LT.h"



std::vector<FST::Fst> Vector_Of_FST(
	{

		//	функции
		FST::Fst((char*)"", FST::lex_funinteger, LEX_FUNCTION, 11,
			FST::NODE(1, FST::RELATION('f', 1)),
			FST::NODE(1, FST::RELATION('u', 2)),
			FST::NODE(1, FST::RELATION('n', 3)),
			FST::NODE(1, FST::RELATION('i', 4)),
			FST::NODE(1, FST::RELATION('n', 5)),
			FST::NODE(1, FST::RELATION('t', 6)),
			FST::NODE(1, FST::RELATION('e', 7)),
			FST::NODE(1, FST::RELATION('g', 8)),
			FST::NODE(1, FST::RELATION('e', 9)),
			FST::NODE(1, FST::RELATION('r', 10)),
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_funstring, LEX_FUNCTION, 10,
			FST::NODE(1, FST::RELATION('f', 1)),
			FST::NODE(1, FST::RELATION('u', 2)),
			FST::NODE(1, FST::RELATION('n', 3)),
			FST::NODE(1, FST::RELATION('s', 4)),
			FST::NODE(1, FST::RELATION('t', 5)),
			FST::NODE(1, FST::RELATION('r', 6)),
			FST::NODE(1, FST::RELATION('i', 7)),
			FST::NODE(1, FST::RELATION('n', 8)),
			FST::NODE(1, FST::RELATION('g', 9)),
			FST::NODE()
		),

		//	переменные
		FST::Fst((char*)"", FST::lex_varinteger, LEX_VARIABLE, 11,
			FST::NODE(1, FST::RELATION('v', 1)),
			FST::NODE(1, FST::RELATION('a', 2)),
			FST::NODE(1, FST::RELATION('r', 3)),
			FST::NODE(1, FST::RELATION('i', 4)),
			FST::NODE(1, FST::RELATION('n', 5)),
			FST::NODE(1, FST::RELATION('t', 6)),
			FST::NODE(1, FST::RELATION('e', 7)),
			FST::NODE(1, FST::RELATION('g', 8)),
			FST::NODE(1, FST::RELATION('e', 9)),
			FST::NODE(1, FST::RELATION('r', 10)),
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_varstring, LEX_VARIABLE, 10,
			FST::NODE(1, FST::RELATION('v', 1)),
			FST::NODE(1, FST::RELATION('a', 2)),
			FST::NODE(1, FST::RELATION('r', 3)),
			FST::NODE(1, FST::RELATION('s', 4)),
			FST::NODE(1, FST::RELATION('t', 5)),
			FST::NODE(1, FST::RELATION('r', 6)),
			FST::NODE(1, FST::RELATION('i', 7)),
			FST::NODE(1, FST::RELATION('n', 8)),
			FST::NODE(1, FST::RELATION('g', 9)),
			FST::NODE()
		),

		//	параметры
		FST::Fst((char*)"", FST::lex_parinteger, LEX_PARAMETR, 11,
			FST::NODE(1, FST::RELATION('p', 1)),
			FST::NODE(1, FST::RELATION('a', 2)),
			FST::NODE(1, FST::RELATION('r', 3)),
			FST::NODE(1, FST::RELATION('i', 4)),
			FST::NODE(1, FST::RELATION('n', 5)),
			FST::NODE(1, FST::RELATION('t', 6)),
			FST::NODE(1, FST::RELATION('e', 7)),
			FST::NODE(1, FST::RELATION('g', 8)),
			FST::NODE(1, FST::RELATION('e', 9)),
			FST::NODE(1, FST::RELATION('r', 10)),
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_parstring, LEX_PARAMETR, 10,
			FST::NODE(1, FST::RELATION('p', 1)),
			FST::NODE(1, FST::RELATION('a', 2)),
			FST::NODE(1, FST::RELATION('r', 3)),
			FST::NODE(1, FST::RELATION('s', 4)),
			FST::NODE(1, FST::RELATION('t', 5)),
			FST::NODE(1, FST::RELATION('r', 6)),
			FST::NODE(1, FST::RELATION('i', 7)),
			FST::NODE(1, FST::RELATION('n', 8)),
			FST::NODE(1, FST::RELATION('g', 9)),
			FST::NODE()
		),

		//	зарезервированные слова
		FST::Fst((char*)"", FST::lex_output, LEX_OUTPUT, 7,
			FST::NODE(1, FST::RELATION('o', 1)),
			FST::NODE(1, FST::RELATION('u', 2)),
			FST::NODE(1, FST::RELATION('t', 3)),
			FST::NODE(1, FST::RELATION('p', 4)),
			FST::NODE(1, FST::RELATION('u', 5)),
			FST::NODE(1, FST::RELATION('t', 6)),
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_recovery, LEX_RECOVERY, 9,
			FST::NODE(1, FST::RELATION('r', 1)),
			FST::NODE(1, FST::RELATION('e', 2)),
			FST::NODE(1, FST::RELATION('c', 3)),
			FST::NODE(1, FST::RELATION('o', 4)),
			FST::NODE(1, FST::RELATION('v', 5)),
			FST::NODE(1, FST::RELATION('e', 6)),
			FST::NODE(1, FST::RELATION('r', 7)),
			FST::NODE(1, FST::RELATION('y', 8)),
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_begin, LEX_BEGIN, 6,
			FST::NODE(1, FST::RELATION('b', 1)),
			FST::NODE(1, FST::RELATION('e', 2)),
			FST::NODE(1, FST::RELATION('g', 3)),
			FST::NODE(1, FST::RELATION('i', 4)),
			FST::NODE(1, FST::RELATION('n', 5)),
			FST::NODE()
		),

		//	литералы
		FST::Fst((char*)"", FST::lex_litinteger, LEX_LITERAL, 2,
			FST::NODE(20,
				FST::RELATION('0', 1), FST::RELATION('0', 0), FST::RELATION('1', 1), FST::RELATION('1', 0),
				FST::RELATION('2', 1), FST::RELATION('2', 0), FST::RELATION('3', 1), FST::RELATION('3', 0),
				FST::RELATION('4', 1), FST::RELATION('4', 0), FST::RELATION('5', 1), FST::RELATION('5', 0),
				FST::RELATION('6', 1), FST::RELATION('6', 0), FST::RELATION('7', 1), FST::RELATION('7', 0),
				FST::RELATION('8', 1), FST::RELATION('8', 0), FST::RELATION('9', 1), FST::RELATION('9', 0)),
			FST::NODE()
		),

		//	знаки, символы-сепараторы
		FST::Fst((char*)"", FST::lex_sign, LEX_SIGN, 2,
			FST::NODE(5,
				FST::RELATION(LEX_DIFFERENCE, 1),							//	-
				FST::RELATION(LEX_SUMM, 1),									//	+
				FST::RELATION(LEX_DIVISION, 1),								//	/
				FST::RELATION(LEX_MULTIPLICATION, 1)),						//	*
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_equally, LEX_EQUALITY, 2,				
			FST::NODE(1, FST::RELATION(LEX_EQUALITY, 1)),					//	=
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_add_this, LEX_LEFT_BRACKET, 2,		
			FST::NODE(1, FST::RELATION(LEX_LEFT_BRACKET, 1)),				//	(
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_add_this, LEX_RIGHT_BRACKET, 2,			
			FST::NODE(1, FST::RELATION(LEX_RIGHT_BRACKET, 1)),				//	)
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_add_this, LEX_SEMICOLON, 2,				
			FST::NODE(1, FST::RELATION(LEX_SEMICOLON, 1)),					//	;
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_add_this, LEX_COMMA, 2,					
			FST::NODE(1, FST::RELATION(LEX_COMMA, 1)),						//	,
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_add_this, LEX_START_PROGRAMM_BLOCK, 2,	
			FST::NODE(1, FST::RELATION(LEX_START_PROGRAMM_BLOCK, 1)),		//	{
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_add_this, LEX_END_PROGRAMM_BLOCK, 2,	
			FST::NODE(1, FST::RELATION(LEX_END_PROGRAMM_BLOCK, 1)),			//	}
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_stlstring, LEX_STANDART_FUNCTION, 10,
			FST::NODE(1, FST::RELATION('s', 1)),
			FST::NODE(1, FST::RELATION('t', 2)),
			FST::NODE(1, FST::RELATION('l', 3)),
			FST::NODE(1, FST::RELATION('s', 4)),
			FST::NODE(1, FST::RELATION('t', 5)),
			FST::NODE(1, FST::RELATION('r', 6)),
			FST::NODE(1, FST::RELATION('i', 7)),
			FST::NODE(1, FST::RELATION('n', 8)),
			FST::NODE(1, FST::RELATION('g', 9)),
			FST::NODE()
		),
		FST::Fst((char*)"", FST::lex_stlinteger, LEX_STANDART_FUNCTION, 11,
			FST::NODE(1, FST::RELATION('s', 1)),
			FST::NODE(1, FST::RELATION('t', 2)),
			FST::NODE(1, FST::RELATION('l', 3)),
			FST::NODE(1, FST::RELATION('i', 4)),
			FST::NODE(1, FST::RELATION('n', 5)),
			FST::NODE(1, FST::RELATION('t', 6)),
			FST::NODE(1, FST::RELATION('e', 7)),
			FST::NODE(1, FST::RELATION('g', 8)),
			FST::NODE(1, FST::RELATION('e', 9)),
			FST::NODE(1, FST::RELATION('r', 10)),
			FST::NODE()
		),

		//	идентификаторы
		FST::Fst((char*)"", FST::lex_id, LEX_ID, 2,
			FST::NODE(104,
				FST::RELATION('a', 0), FST::RELATION('a', 1), FST::RELATION('b', 0), FST::RELATION('b', 1),
				FST::RELATION('c', 0), FST::RELATION('c', 1), FST::RELATION('d', 0), FST::RELATION('d', 1),
				FST::RELATION('e', 0), FST::RELATION('e', 1), FST::RELATION('f', 0), FST::RELATION('f', 1),
				FST::RELATION('g', 0), FST::RELATION('g', 1), FST::RELATION('h', 0), FST::RELATION('h', 1),
				FST::RELATION('i', 0), FST::RELATION('i', 1), FST::RELATION('j', 0), FST::RELATION('j', 1),
				FST::RELATION('k', 0), FST::RELATION('k', 1), FST::RELATION('l', 0), FST::RELATION('l', 1),
				FST::RELATION('m', 0), FST::RELATION('m', 1), FST::RELATION('n', 0), FST::RELATION('n', 1),
				FST::RELATION('o', 0), FST::RELATION('o', 1), FST::RELATION('p', 0), FST::RELATION('p', 1),
				FST::RELATION('q', 0), FST::RELATION('q', 1), FST::RELATION('r', 0), FST::RELATION('r', 1),
				FST::RELATION('s', 0), FST::RELATION('s', 1), FST::RELATION('t', 0), FST::RELATION('t', 1),
				FST::RELATION('u', 0), FST::RELATION('u', 1), FST::RELATION('v', 0), FST::RELATION('v', 1),
				FST::RELATION('w', 0), FST::RELATION('w', 1), FST::RELATION('x', 0), FST::RELATION('x', 1),
				FST::RELATION('y', 0), FST::RELATION('y', 1), FST::RELATION('z', 0), FST::RELATION('z', 1),
				FST::RELATION('A', 0), FST::RELATION('A', 1), FST::RELATION('B', 0), FST::RELATION('B', 1),
				FST::RELATION('C', 0), FST::RELATION('C', 1), FST::RELATION('D', 0), FST::RELATION('D', 1),
				FST::RELATION('E', 0), FST::RELATION('E', 1), FST::RELATION('F', 0), FST::RELATION('F', 1),
				FST::RELATION('G', 0), FST::RELATION('G', 1), FST::RELATION('H', 0), FST::RELATION('H', 1),
				FST::RELATION('I', 0), FST::RELATION('I', 1), FST::RELATION('J', 0), FST::RELATION('J', 1),
				FST::RELATION('K', 0), FST::RELATION('K', 1), FST::RELATION('L', 0), FST::RELATION('L', 1),
				FST::RELATION('M', 0), FST::RELATION('M', 1), FST::RELATION('N', 0), FST::RELATION('N', 1),
				FST::RELATION('O', 0), FST::RELATION('O', 1), FST::RELATION('P', 0), FST::RELATION('P', 1),
				FST::RELATION('Q', 0), FST::RELATION('Q', 1), FST::RELATION('R', 0), FST::RELATION('R', 1),
				FST::RELATION('S', 0), FST::RELATION('S', 1), FST::RELATION('T', 0), FST::RELATION('T', 1),
				FST::RELATION('U', 0), FST::RELATION('U', 1), FST::RELATION('V', 0), FST::RELATION('V', 1),
				FST::RELATION('W', 0), FST::RELATION('W', 1), FST::RELATION('X', 0), FST::RELATION('X', 1),
				FST::RELATION('Y', 0), FST::RELATION('Y', 1), FST::RELATION('Z', 0), FST::RELATION('Z', 1)),
			FST::NODE()
		)
	}
);
