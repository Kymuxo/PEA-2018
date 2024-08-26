#pragma once

#include "stdafx.h"
#include "IT.h"
#include "ERROR.h"



int kol_functions = 0;

void IT::Add(IT::IdTable& idtable, IT::Entry entry)
{
	check_on_fill_out(idtable);
	idtable.table[idtable.size++] = entry;
	check_on_fill_out(idtable);
};

void IT::Delete(IdTable& idtable)
{
	delete[] & idtable;
}

IT::IdTable IT::Create(int size)
{
	IdTable* New = new IdTable;
	New->maxsize = size;
	New->size = 0;
	New->table = new Entry[size];

	return *New;
}

void IT::fill_for_idxTI(IdTable& idtable, IT::Entry &for_return, int idxfirstLEp, std::string idp, int iddatatypep, int idtypep, std::string visibility)
{
	if (idtypep == IDTYPE::F)	
		idtable.kol_functions++;
	else if (idtypep == IDTYPE::L)	
		idtable.kol_literals++;
	else if (idtypep == IDTYPE::P)	
		idtable.kol_parametrs++;
	else if (idtypep == IDTYPE::V)	
		idtable.kol_variables++;

	check_on_fill_out(idtable);

	IT::check_on_fill_out(idtable);

	for_return.first_line = idxfirstLEp;
	for_return.id = idp;

	for_return.iddatatype = iddatatypep;
	for_return.idtype = idtypep;

	for_return.value.vint = 0;
	for_return.value.vstr = "";

	for_return.visibility_area = visibility;
}

void IT::fill_string(IdTable& idtable, int idxfirstLEp, std::string idp, int iddatatypep, int idtypep, std::string visibility, std::string vstr_sp)//для литералов
{
	Entry for_return;
	IT::fill_for_idxTI(idtable, for_return, idxfirstLEp, idp, iddatatypep, idtypep, visibility);
	for_return.value.vstr = vstr_sp;
	IT::Add(idtable, for_return);
	idtable.table[idtable.size - 1].id += to_string(idtable.kol_literals);
}

void IT::fill_int(IdTable& idtable, int idxfirstLEp, std::string idp, int iddatatypep, int idtypep, std::string visibility, std::string vintp)//для литералов
{
	if (vintp.length()>10)
		throw ERROR_THROW((int)406);
	
	long long buffer = 0;
	
	for (int i = 0; i < vintp.length(); i++)
	{
		buffer *= 10;
		buffer += vintp[i] - '0';
	}
	
	if (buffer > INT_MAX)
		throw ERROR_THROW((int)406);

	Entry for_return;
	IT::fill_for_idxTI(idtable, for_return, idxfirstLEp, idp, iddatatypep, idtypep, visibility);
	for_return.value.vint = (int)buffer;


	IT::Add(idtable, for_return);
	idtable.table[idtable.size - 1].id += to_string(idtable.kol_literals);
}

void IT::print_info_id(IdTable idtable, LOG log)
{
	log.WriteLine("Количество литералов в таблице \t\t\t: " + to_string(idtable.kol_literals) + "\nКоличество функций в таблице \t\t\t: " + 
		to_string(idtable.kol_functions) + "\nКоличество переменных в таблице \t\t: " + to_string(idtable.kol_variables) + "\nКоличество параметров функций в таблице : " + 
		to_string(idtable.kol_parametrs) + "\nВсего идентификаторов \t\t\t\t\t: " + to_string(idtable.size) + "\n\n", (*log.stream_for_log));
}

void IT::fill_without_id(IdTable& idtable, int idxfirstLEp, int iddatatypep, int idtypep, std::string visibility)
{
	idtable.table[idtable.size].first_line = idxfirstLEp;
	idtable.table[idtable.size].iddatatype = iddatatypep;
	idtable.table[idtable.size].idtype = idtypep;
	idtable.table[idtable.size].visibility_area = visibility;

	idtable.table[idtable.size].value.vint = 0;
	idtable.table[idtable.size].value.vstr = "";

	if (idtypep == IT::F)
		idtable.kol_functions++;
	
	if (idtypep == IT::V)
		idtable.kol_variables++;
	
	if (idtypep == IT::L)
		idtable.kol_literals++;
	
	if (idtypep == IT::P)
		idtable.kol_parametrs++;

	idtable.size++;
}

void IT::fill_only_id(IdTable& idtable, std::string idp)
{
	idtable.table[idtable.size - 1].id = idp;
}

void IT::check_on_fill_out(IdTable idtable)
{
	if (idtable.kol_functions >	IT_MAX_SIZE_FUNCTIONS)
		throw ERROR_THROW(311);
	
	if (idtable.kol_literals  >	IT_MAX_SIZE_LITERALS)	
		throw ERROR_THROW(312);
	
	if (idtable.kol_variables >	IT_MAX_SIZE_VARIABLES)		
		throw ERROR_THROW(313);
	
	if (idtable.kol_parametrs >	IT_MAX_SIZE_PARAMETRS)		
		throw ERROR_THROW(314);
}