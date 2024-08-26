#include "stdafx.h"
#include "Output_functions.h"



void OF::output_lexems(LT::LexTable &Lex_Table, LOG log, IN in)
{
	log.WriteLine("Всего лексем : " + to_string(Lex_Table.size) + "\n", (*log.stream_for_log));
	
	for (int i = 0; i < Lex_Table.size; i++)
	{
		if (Lex_Table.table[i].line_code != Lex_Table.table[i - 1].line_code)
		{
			log.WriteLine("\n" + to_string(Lex_Table.table[i].line_code) + " ", (*log.stream_for_log));
		}
		
		log.WriteLine(Lex_Table.table[i].lexema, (*log.stream_for_log));
	}
	
	log.WriteLine("\n\nLC\t№LT\tLex\t№IT\t№IN\n", (*log.stream_for_log));

	for (int i = 0; i < Lex_Table.size; i++)
	{
		log.WriteLine(to_string(Lex_Table.table[i].line_code) + "\t" + to_string(i) + "\t" + Lex_Table.table[i].lexema + "\t", (*log.stream_for_log));
		
		if (Lex_Table.table[i].number_in_id == -1)
		{
			if (Lex_Table.table[i].number_in_input == -1)
				log.WriteLine("#\t#\n", (*log.stream_for_log));
			else
				log.WriteLine("#\t" + to_string(Lex_Table.table[i].number_in_input) + "\n", (*log.stream_for_log));
		}
		else
		{
			if (Lex_Table.table[i].number_in_input == -1)
				log.WriteLine(to_string(Lex_Table.table[i].number_in_id) + "\t#\n", (*log.stream_for_log));
			else
				log.WriteLine(to_string(Lex_Table.table[i].number_in_id) + "\t" + to_string(Lex_Table.table[i].number_in_input) + "\n", (*log.stream_for_log));
		}
	}
}

void OF::Output_identifikators(IT::IdTable &ID_Table, LOG log)
{
	IT::print_info_id(ID_Table, log);

	log.WriteLine("List of identifikators, literals\nnumber\tname\tidtype\tlinecode\tvalue\n", (*log.stream_for_log));

	for (int i = 0; i < ID_Table.size; i++)
	{
		if (ID_Table.table[i].idtype == IT::L)
		{
			IT::Entry entry = ID_Table.table[i];

			log.WriteLine(to_string(i) + "\t" + entry.id + "\t", (*log.stream_for_log));
			
			if (entry.iddatatype == IT::STR)	
				log.WriteLine("string", (*log.stream_for_log));
			
			if (entry.iddatatype == IT::INT)	
				log.WriteLine("integer", (*log.stream_for_log));
			
			log.WriteLine("\t" + to_string(entry.first_line), (*log.stream_for_log));
			
			if (entry.iddatatype == IT::STR)	
				log.WriteLine("\t\t\"" + entry.value.vstr + '"', (*log.stream_for_log));
			
			if (entry.iddatatype == IT::INT)	
				log.WriteLine("\t\t" + to_string(entry.value.vint), (*log.stream_for_log));
			
			log.WriteLine("\n", (*log.stream_for_log));
		}
	}
	
	log.WriteLine("\nList of identifikators, variables\nnumber\tname\tidtype\tlinecode\tinit_value\n", (*log.stream_for_log));
	
	for (int i = 0; i < ID_Table.size; i++)
	{
		if (ID_Table.table[i].idtype == IT::V)
		{
			IT::Entry entry = ID_Table.table[i];
			log.WriteLine(to_string(i) + "\t" + entry.id + "\t", (*log.stream_for_log));
			
			if (entry.iddatatype == IT::INT) 
				log.WriteLine("INT\t", (*log.stream_for_log));
			
			if (entry.iddatatype == IT::STR) 
				log.WriteLine("STR\t", (*log.stream_for_log));
			
			log.WriteLine(to_string(entry.first_line) + "\t\t", (*log.stream_for_log));
			
			if (entry.iddatatype == IT::INT)	
				log.WriteLine(to_string(entry.value.vint), (*log.stream_for_log));
			
			if (entry.iddatatype == IT::STR)	
				log.WriteLine('"' + entry.value.vstr + '"' + "\t", (*log.stream_for_log));
			
			log.WriteLine("\nvisibility area: " + entry.visibility_area + "\n", (*log.stream_for_log));

		}
	}
	
	log.WriteLine("\nList of identifikators, parametrs\nnumber\tname\ttype\tlinecode\n", (*log.stream_for_log));
	
	for (int i = 0; i < ID_Table.size; i++)
	{
		if (ID_Table.table[i].idtype == IT::P)
		{
			IT::Entry entry = ID_Table.table[i];
			log.WriteLine(to_string(i) + "\t" + entry.id + "\t", (*log.stream_for_log));
			
			if (entry.iddatatype == IT::INT)	
				log.WriteLine("integer\t", (*log.stream_for_log));
			
			if (entry.iddatatype == IT::STR)	
				log.WriteLine("string\t", (*log.stream_for_log));
			
			log.WriteLine(to_string(entry.first_line) + "\nvisibility area: " + entry.visibility_area + "\n", (*log.stream_for_log));
		}
	}
	
	log.WriteLine("\nList of identifikators, functions\nnumber\tname\tlinecode\ttype\n", (*log.stream_for_log));
	
	for (int i = 0; i < ID_Table.size; i++)
	{
		if (ID_Table.table[i].idtype == IT::F)
		{
			IT::Entry entry = ID_Table.table[i];
			log.WriteLine(to_string(i) + "\t" + entry.id + "\t" + to_string(entry.first_line) + "\t\t", (*log.stream_for_log));
			
			if (entry.iddatatype == IT::STR)
				log.WriteLine("string", (*log.stream_for_log));
			else if (entry.iddatatype == IT::INT)
				log.WriteLine("integer", (*log.stream_for_log));
			
			log.WriteLine("\nvisibility area: " + entry.visibility_area + "\n", (*log.stream_for_log));
		}
	}
}