#include "stdafx.h"
#include "LT.h"
#include "LOG.h"
#include "IT.h"
#include "ERROR.h"



void check_on_noinit_per(LT::LexTable lextable, LOG log, IT::IdTable ID_Table)
{
	bool check = false;
	
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_ID && lextable.table[i].number_in_id == -1)
		{
			check = true;
			log.WriteLine("Использована необъявленная локальная переменная/функция! Строка: " + to_string(lextable.table[i].line_code) + "\n", (*log.stream_for_log));
		}
	
	if (check == true)
		throw ERROR_THROW((int)401);
}

void check_on_point_input(LT::LexTable lextable, LOG log)
{
	int kol = 0;
	
	for (int i = 0; i < lextable.size && kol < 3; i++)
		if (lextable.table[i].lexema == LEX_BEGIN)
			kol++;
	
	if (kol == 0)
		throw ERROR_THROW((int)400);
	
	if (kol > 1)
		throw ERROR_THROW((int)408);
}

void formal_and_actual_parameters_match(LT::LexTable lextable, LOG log, IT::IdTable idtable)//+
{
	for (int i = 0; i < idtable.size; i++)
		if (idtable.table[i].idtype == IT::F)
		{
			int kol = 0;
			int j = 0;
			
			for (j = i + 1; idtable.table[j].idtype == IT::P; j++)
				kol++;
			
			if (kol > IT_MAX_KOL_PAMS_ON_FUNCTION)
				throw Error::geterrorin(402, idtable.table[j].first_line, idtable.table[i].id);
		}
	
	for (int i = 0; i < idtable.size; i++)
		if (idtable.table[i].idtype == IT::F)
			for (int j = i + 1; j < idtable.size; j++)
				if (idtable.table[j].idtype == IT::F && idtable.table[i].id == idtable.table[j].id &&
					idtable.table[j].visibility_area == idtable.table[i].visibility_area && idtable.table[i].visibility_area != FLAG_ST_F)
					throw Error::geterrorin(409, idtable.table[j].first_line, idtable.table[i].id);

	for (int i = 2; i < lextable.size; i++)
	{
		if (lextable.table[i - 2].lexema == LEX_ID && lextable.table[i - 1].lexema == LEX_EQUALITY)
		{
			int type_ish = idtable.table[lextable.table[i - 2].number_in_id].iddatatype;
			int kol = 0;
			
			while (lextable.table[i].lexema != LEX_SEMICOLON)
			{
				if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].number_in_id].iddatatype != type_ish)
					throw Error::geterrorin(413, lextable.table[i].line_code, idtable.table[lextable.table[i].number_in_id].id);

				if (lextable.table[i].lexema == LEX_LITERAL && idtable.table[lextable.table[i].number_in_id].iddatatype != type_ish)
					throw Error::geterrorin(413, lextable.table[i].line_code, idtable.table[i].id);
				
				if (lextable.table[i].lexema == LEX_ID && lextable.table[i + 1].lexema == LEX_LEFT_BRACKET)
				{
					kol++;
					
					while (lextable.table[i].lexema != LEX_RIGHT_BRACKET)
						i++;
				}
				
				if (lextable.table[i].lexema != LEX_SIGN && lextable.table[i].lexema != LEX_LEFT_BRACKET && lextable.table[i].lexema != LEX_RIGHT_BRACKET)
					kol++;
				
				if (kol > 1 && type_ish == IT::STR)
					throw Error::geterrorin(410, lextable.table[i].line_code, idtable.table[i].id);
				
				i++;
				
				if (i == lextable.size)
					break;
			}
			
			if (i == lextable.size)
				break;
		}
	}

}

void check_double_names_id(IT::IdTable idtable, LOG log)
{
	for (int i = 0; i < idtable.size; i++)
		for (int j = i + 1; j < idtable.size; j++)
		{
			if (idtable.table[i].id == idtable.table[j].id && idtable.table[j].idtype != IT::L && idtable.table[j].idtype != IT::P &&
				idtable.table[i].visibility_area == idtable.table[j].visibility_area &&	idtable.table[i].visibility_area != FLAG_ST_F)
				throw ERROR_THROW(405);
			
			if (idtable.table[i].id == idtable.table[j].id && idtable.table[j].idtype != IT::L && idtable.table[j].idtype != IT::P &&
				(idtable.table[i].visibility_area == "" || idtable.table[j].visibility_area == "") && idtable.table[i].visibility_area != FLAG_ST_F)
				throw ERROR_THROW(405);
			
			if (idtable.table[i].id == idtable.table[j].id	&& idtable.table[j].idtype == IT::P	&&
				idtable.table[i].visibility_area == idtable.table[j].visibility_area && idtable.table[i].visibility_area != FLAG_ST_F &&
				idtable.table[i].first_line == idtable.table[j].first_line)
				throw ERROR_THROW(405);
		}
}

void check_on_parms_in_f(LT::LexTable lextable, LOG log, IT::IdTable idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_ID && lextable.table[i + 1].lexema == LEX_LEFT_BRACKET && lextable.table[i - 1].lexema != LEX_STANDART_FUNCTION && 
			lextable.table[i - 1].lexema != LEX_FUNCTION)
		{
			int number = lextable.table[i].number_in_id;
			int kol_in_line = 0;
			int kol_in_f = 0;
			
			for (int j = i + 2; lextable.table[j].lexema != LEX_RIGHT_BRACKET && lextable.table[j - 1].lexema != LEX_RIGHT_BRACKET; j += 2)
				kol_in_line++;
			
			for (int j = number + 1; idtable.table[j].idtype == IT::P; j++)
				kol_in_f++;
			
			if (kol_in_f != kol_in_line)
				throw ERROR_THROW(404);
			
			number++;
			i += 2;
			
			while (lextable.table[i - 1].lexema != LEX_RIGHT_BRACKET && lextable.table[i].lexema != LEX_RIGHT_BRACKET && lextable.table[i - 2].lexema != LEX_RIGHT_BRACKET)
			{
				if (idtable.table[lextable.table[i].number_in_id].iddatatype != idtable.table[number].iddatatype)
				{
					log.WriteLine("Ошибка в " + idtable.table[lextable.table[i - 2].number_in_id].id + "\n", (*log.stream_for_log));
					throw ERROR_THROW(403);
				}
				
				number++;
				i += 2;
			}
		}
	}
}

void check_on_return_value(LT::LexTable lextable, LOG log, IT::IdTable idtable)
{
	for (int i = 0; i < lextable.size - 1; i++)
	{
		std::string buffer = "";
		int buff = -1;
		
		if (lextable.table[i].lexema == LEX_FUNCTION && idtable.table[lextable.table[i + 1].number_in_id].idtype == IT::F)
		{
			i++;
			buffer = idtable.table[lextable.table[i].number_in_id].id;
			buff = idtable.table[lextable.table[i].number_in_id].first_line;
			int type_return_from_start = idtable.table[lextable.table[i].number_in_id].iddatatype;
			
			while (lextable.table[i - 1].lexema != LEX_RECOVERY && i < lextable.size)
			{
				i++;
				
				if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].number_in_id].id == buffer)
					throw Error::geterrorin(414, -1, buffer);

			}
			
			if (idtable.table[lextable.table[i].number_in_id].idtype == IT::F || idtable.table[lextable.table[i].number_in_id].idtype == IT::L)
				throw ERROR_THROW(412);
			
			int type_return_in_giveaway = idtable.table[lextable.table[i].number_in_id].iddatatype;
			
			if (type_return_from_start != type_return_in_giveaway)
				throw ERROR_THROW(407);
		}
	}
}

void for_411(LT::LexTable lextable, IT::IdTable idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_ID && lextable.table[i + 1].lexema == LEX_EQUALITY &&
			lextable.table[i + 3].lexema == LEX_LEFT_BRACKET && idtable.table[lextable.table[i].number_in_id].iddatatype == IT::STR)
		{
			
			while (lextable.table[i].lexema != LEX_RIGHT_BRACKET)
				i++;
			
			if (lextable.table[i + 1].lexema != LEX_SEMICOLON)
				throw ERROR_THROW(413);
		}
	}
	
	int kol = 0;
	int kol1, kol2, kol3;
	kol1 = kol2 = kol3 = 0;
	
	for (int i = 0; i < idtable.size; i++)
	{
		if (idtable.table[i].id == NAME_STANDART_F_lenstr)
			kol1++;
		
		if (idtable.table[i].id == NAME_STANDART_F_strsub)
			kol2++;
		
		if (idtable.table[i].id == NAME_STANDART_F_concat)
			kol3++;
	}
	
	if (kol1 > 1 || kol2 > 1 || kol3 > 1)
		throw ERROR_THROW((int)411);
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_STANDART_FUNCTION)
			kol++;
		
		if (kol > 3)
			throw ERROR_THROW(411);
	}
}

void semantic_analiz_last_part(LT::LexTable lextable, LOG log, IT::IdTable idtable)
{
	check_on_noinit_per(lextable, log, idtable);
	check_on_point_input(lextable, log);
	formal_and_actual_parameters_match(lextable, log, idtable);
	check_double_names_id(idtable, log);
	check_on_parms_in_f(lextable, log, idtable);
	check_on_return_value(lextable, log, idtable);
	for_411(lextable, idtable);
	log.WriteLine("Вынесенная из программы часть семантического анализа выполнена успешно!\n", (*log.stream_for_log));
}