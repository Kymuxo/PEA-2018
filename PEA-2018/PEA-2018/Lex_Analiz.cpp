#pragma once

#include "stdafx.h"
#include "FST.h"
#include "LT.h"
#include "LOG.h"
#include "IN.h"
#include "PARM.h"
#include "IT.h"
#include "Automats.h"



LT::Entry Lex_To_Add;																						//	временная лексема

int get_number_working_auto(LT::LexTable &Lex_Table, int &linecode, string lexem, int number_in_text)		//	Проверка на работу автоматов элементов вектора
{
	for (int i = 0; i < (int)(Vector_Of_FST.size()); i++)
	{
		FST::setFST(Vector_Of_FST[i], lexem);

		if (FST::execute(Vector_Of_FST[i]) == true)
		{
			if (Vector_Of_FST[i].lexem_to_return == LEX_SEMICOLON && Lex_Table.table[Lex_Table.size - 1].lexema == LEX_SEMICOLON)
				return FST::lex_NO_RESULT;

			if (Lex_Table.table[Lex_Table.size - 1].line_code == linecode - 2)
				linecode--;

			Lex_To_Add.lexema = Vector_Of_FST[i].lexem_to_return;
			Lex_To_Add.line_code = linecode;
			Lex_To_Add.number_in_input = number_in_text;
			LT::Add(Lex_Table, Lex_To_Add);

			return Vector_Of_FST[i].number;
		}
	}

	return FST::lex_NO_RESULT;
}

int get_number_to_LT_for_id(IT::IdTable &idtable, std::string &id, std::string current_visibility)
{
	for (int i = idtable.size - 1; i > -1; i--)
	{
		if (idtable.table[i].id == id && idtable.table[i].visibility_area == current_visibility)
			return i;

		if (idtable.table[i].id == id && idtable.table[i].idtype == IT::F)
			return i;

		if (idtable.table[i].id == id && idtable.table[i].visibility_area == FLAG_ST_F)
			return i;
	}

	return -1;
}

void LexAnaliz(IN in, LOG log, PARMS Parms, LT::LexTable &Lex_Table, IT::IdTable &ID_Table)
{
	std::string Words_string = "";
	int linecode = -3;
	int kol_errors_in_LA = 0;
	std::string visibility1 = "";
	std::string visibility2 = "";

	for (unsigned int i = 0; i < in.text.length(); i++)
	{
		std::string visibility3 = (visibility2 == "") ? visibility1 : visibility2;

		if (in.text[i] == LEX_END_PROGRAMM_BLOCK)
			visibility1 = "";

		if (in.text[i] == LEX_SEMICOLON)
			visibility2 = "";

		if (ine(in.text[i]) == IN::Q)
		{
			string string_for_add = "";
			Lex_To_Add.lexema = LEX_LITERAL;
			Lex_To_Add.line_code = linecode;
			Lex_To_Add.number_in_input = i;
			LT::Add(Lex_Table, Lex_To_Add);
			Lex_Table.table[Lex_Table.size - 1].number_in_id = ID_Table.size;
			i++;

			while (ine(in.text[i]) != IN::Q)
			{
				string_for_add += in.text[i];
				i++;
			}

			IT::fill_string(ID_Table, linecode, FLAG_LIT, IT::STR, IT::L, visibility3, string_for_add);

			continue;
		}
		else if ((IN::code[in.text[i]] == IN::D || IN::code[in.text[i]] == IN::G || IN::code[in.text[i]] == IN::A) && Words_string == "")
		{
			char *str = new char[2];
			str[0] = in.text[i];
			str[1] = '\0';
			get_number_working_auto(Lex_Table, linecode, str, i);

			delete str;
		}
		else if ((IN::code[in.text[i]] == IN::D || IN::code[in.text[i]] == IN::S || IN::code[in.text[i]] == IN::G || IN::code[in.text[i]] == IN::A) && Words_string != "")
		{
			int number_working_auto = get_number_working_auto(Lex_Table, linecode, Words_string, i - Words_string.length());

			switch (number_working_auto)
			{
				case FST::lex_add_this:
					LT::Add(Lex_Table, Lex_To_Add);
					break;
				case FST::lex_funinteger:
					visibility1 = FLAG_FUN;
					IT::fill_without_id(ID_Table, linecode, IT::INT, IT::F, "");
					break;
				case FST::lex_funstring:
					visibility1 = FLAG_FUN;
					IT::fill_without_id(ID_Table, linecode, IT::STR, IT::F, "");
					break;
				case FST::lex_begin:
					visibility1 = FLAG_MAIN;
					IT::fill_without_id(ID_Table, linecode, IT::INT, IT::F, FLAG_MAIN);
					Lex_Table.table[Lex_Table.size - 1].number_in_id = ID_Table.size - 1;
					IT::fill_only_id(ID_Table, FLAG_MAIN);
					break;
				case FST::lex_stlstring:
					visibility2 = FLAG_FUN;
					IT::fill_without_id(ID_Table, linecode, IT::STR, IT::F, FLAG_ST_F);
					break;
				case FST::lex_stlinteger:
					visibility2 = FLAG_FUN;
					IT::fill_without_id(ID_Table, linecode, IT::INT, IT::F, FLAG_ST_F);
					break;
				case FST::lex_id:																								//	Идентификатор
				{
					if (Words_string.length() > WORDSLENGTH)
					{
						std::string buffer = "";

						for (int i = 0; i < WORDSLENGTH; i++)
							buffer += Words_string[i];

						Words_string = buffer;
					}

					if (visibility2 == FLAG_FUN)
						visibility2 += Words_string;
					else if (visibility1 == FLAG_FUN)
						visibility1 += Words_string;
				
					if (Lex_Table.table[Lex_Table.size - 2].lexema == LEX_FUNCTION || Lex_Table.table[Lex_Table.size - 2].lexema == LEX_VARIABLE ||
					Lex_Table.table[Lex_Table.size - 2].lexema == LEX_STANDART_FUNCTION || Lex_Table.table[Lex_Table.size - 2].lexema == LEX_PARAMETR)
						IT::fill_only_id(ID_Table, Words_string);
					
					Lex_Table.table[Lex_Table.size - 1].number_in_id = get_number_to_LT_for_id(ID_Table, Words_string, visibility3); // связывает лексему с соответствующим идентификатором
				}
					break;
				case FST::lex_litinteger:
					IT::fill_int(ID_Table, linecode, FLAG_LIT, IT::INT, IT::L, visibility1, Words_string);
					Lex_Table.table[Lex_Table.size - 1].number_in_id = ID_Table.size - 1;
					break;
				case FST::lex_varinteger:
					IT::fill_without_id(ID_Table, linecode, IT::INT, IT::V, visibility3);
					break;
				case FST::lex_varstring:
					IT::fill_without_id(ID_Table, linecode, IT::STR, IT::V, visibility3);
					break;
				case FST::lex_parinteger:
					IT::fill_without_id(ID_Table, linecode, IT::INT, IT::P, visibility3);
					break;
				case FST::lex_parstring:
					IT::fill_without_id(ID_Table, linecode, IT::STR, IT::P, visibility3);
					break;
				case FST::lex_NO_RESULT:
				{
					if (Words_string[0] != (char)32)
					{
						kol_errors_in_LA++;
						log.WriteLine("Не удалось преобразовать слово в лексему " + Words_string, (*log.stream_for_log));
					
						if (kol_errors_in_LA > MAX_KOL_ERRORS_IN_LA)
							throw ERROR_THROW(300);
					}
				}
					break;
				default:
					break;
			}
			
			if (IN::code[in.text[i]] != IN::S)
			{
				Words_string = in.text[i];
				get_number_working_auto(Lex_Table, linecode, Words_string, i);
			}
			
			Words_string = "";
		}
		else
		{
			if (in.text[i] == '\n')
			{
				linecode++;
				
				continue;
			}
			
			Words_string += in.text[i];
		}
	}
	
	if (kol_errors_in_LA > 0)
		throw ERROR_THROW(300);
}