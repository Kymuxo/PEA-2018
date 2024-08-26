#pragma once

#include "LOG.h"
#include <iostream>



#define WORDSLENGTH 10
#define IT_MAX_SIZE				4000
#define IT_MAX_SIZE_LITERALS	1000
#define IT_MAX_SIZE_VARIABLES	1000
#define IT_MAX_SIZE_PARAMETRS	1000
#define IT_MAX_SIZE_FUNCTIONS	1000
#define IT_MAX_KOL_PAMS_ON_FUNCTION 10


namespace IT
{
	enum IDDATATYPE { INT, STR };											//	тип переменной INT-integer, STR-string
	enum IDTYPE { V, F, P, L };												//	V-переменная F-функция P-параметр L-литерал

	struct Entry
	{
		int			first_line;
		int			iddatatype;												// INT STR
		int			idtype;													// V   F   P    L
		std::string id;
		
		struct
		{
			int vint = NULL;
			std::string vstr;
		} value;
		
		std::string visibility_area = "";
	};

	struct IdTable
	{
		int maxsize;
		int size;
		Entry* table;
		int kol_literals = 0;
		int kol_variables = 0;
		int kol_functions = 0;
		int kol_parametrs = 0;
	};
	
	void print_info_id(IdTable idtable, LOG log);
	void check_on_fill_out(IdTable idtable);
	void fill_for_idxTI(IdTable& idtable, Entry &for_return, int idxfirstLEp, std::string idp, int iddatatypep, int idtypep, std::string visibility);

	void fill_string(IdTable& idtable, int idxfirstLEp, std::string idp, int iddatatypep, int idtypep, std::string visibility, std::string vstr_sp);
	void fill_int(IdTable& idtable, int idxfirstLEp, std::string idp, int iddatatypep, int idtypep, std::string visibility, std::string vintp);

	void fill_without_id(IdTable& idtable, int idxfirstLEp, int iddatatypep, int idtypep, std::string visibility);
	void fill_only_id(IdTable& idtable, std::string idp);

	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);

	void Delete(IdTable& idtable);
};