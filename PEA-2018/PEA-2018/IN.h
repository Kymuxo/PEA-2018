#pragma once

#include "stdafx.h"
#include <fstream>
#include "ERROR.h"



#define STR_MAXSIZE  200
#define ine(buffer) IN::code[(int)buffer]
//	         0	    1      2      3      4      5      6      7      8      9      10     11     12     13     14     15
#define IN_CODE_TABLE {\
	/*  0*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::P, IN::N, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/* 16*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/* 32*/IN::S, IN::F, IN::Q, IN::F, IN::F, IN::F, IN::F, IN::F, IN::D, IN::D, IN::A, IN::A, IN::D, IN::A, IN::F, IN::A,\
	/* 48*/IN::L, IN::L, IN::L, IN::L, IN::L, IN::L, IN::L, IN::L, IN::L, IN::L, IN::F, IN::D, IN::F, IN::G, IN::F, IN::F,\
	/* 64*/IN::F, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E,\
	/* 80*/IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/* 96*/IN::F, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E,\
	/*112*/IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::E, IN::D, IN::F, IN::D, IN::F, IN::F,\
	\
	/*128*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*144*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*160*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*176*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*192*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*208*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*224*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*240*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F\
}


using namespace std;


class IN
{
	public:
		enum {
			E, //	E-символы латинского алфавита
			F, //	F-запрещен
			N, //	N-символ новой строки
			L, //	L-цифры
			D, //	D(delimiter) -скобки, точка с запятой, запятая
			A, //	A(action badge)-знаки действий( + - * /)
			S, //	S-пробел
			Q, //	Q-двойная кавычка
			G, //	G - '='
   			P  //	9 символ Табуляция
		};
	int kol_lines = 0;
	int kol_errors = 0;


	string text = "";
	static int code[256];

	void getin(wchar_t input_file[], std::ofstream *output_file)
	{

		ifstream file(input_file);
		
		if (!file)
		{
			throw ERROR_THROW(110);
		}
		else
		{
			unsigned char buffer;
			int linecode = 0;
			text = "stlstring concat(parstring a,parstring b);\nstlstring strsub(parstring a,parinteger b,parinteger c);\nstlinteger lenstr(parstring a);\n";
			
			while ((buffer = file.get()) && !file.eof())
			{
				if (file.eof())
					break;
				
				if (buffer == ' ' || buffer == '\n' || buffer == '\t' || buffer == ';')
				{
					bool check = false;
					bool check_n = false;
					
					while (buffer == ' ' || buffer == '\n' || buffer == '\t' || buffer == ';')
					{
						if (buffer == '\n')
							check_n = true;
						if (buffer == ';')
							check = true;
						buffer = file.get();
						if (file.eof())
							break;
						if (buffer == ';')
							check = true;
						if (buffer == '\n')
							check_n = true;
					}
					
					if (file.eof())
						break;
					
					if (buffer == LEX_END_PROGRAMM_BLOCK || buffer == LEX_START_PROGRAMM_BLOCK)
					{
						if (buffer == LEX_END_PROGRAMM_BLOCK)
							text += ';';
						
						text += "\n";
						text += buffer;
						text += "\n";
						
						continue;
					}
					
					if (check == true)
					{
						if (ine(text[text.length() - 1]) == IN::E || ine(text[text.length() - 1]) == IN::L || ine(text[text.length() - 1]) == IN::Q || ine(text[text.length() - 1]) == IN::D)
							text += ";\n";
						else 
							text += "\n";
						
						text += buffer;
						
						continue;
					}
					
					if (text[text.length() - 1] == ';')
						text += "\n";
					
					if (text[text.length() - 1] != ';' && ((ine(text[text.length() - 1]) == IN::E) && (ine(buffer) == IN::L || ine(buffer) == IN::E)))
						text += ' ';
					
					if (buffer == LEX_END_PROGRAMM_BLOCK)
					{
						text += buffer;
						
						continue;
					}
					
					if (check_n == true && (text[text.length() - 2] == ')' || ine(text[text.length() - 2]) == IN::E || ine(text[text.length() - 2]) == IN::L) && text[text.length() - 1] == '\n')
					{
						text[text.length() - 1] = ';';
						text += "\n";
					}
					
					if (file.eof())
						break;
				}
				
				if (buffer == LEX_SEMICOLON && text[text.length() - 1] == LEX_END_PROGRAMM_BLOCK)
				{
					text += '\n';
					
					continue;
				}
				
				if (buffer == LEX_SEMICOLON)
				{
					while (buffer == LEX_SEMICOLON || buffer == '\n' || buffer == ' ')
					{
						buffer = file.get();
						
						if (file.eof())
							break;
					}
					
					text += LEX_SEMICOLON;
					text += '\n';
				}

				if (ine(buffer) == IN::Q)
				{
					text += " ";
					int kol = 0;
					text += buffer;
					buffer = file.get();
					text += buffer;
					
					if (ine(buffer) == IN::Q)
						throw ERROR_THROW(118);
					
					while (ine(buffer) != IN::Q)
					{
						if (file.eof())
							throw ERROR_THROW(117);
						
						buffer = file.get();
						
						if ((ine(buffer) != IN::F) && (ine(buffer) != IN::P && ine(buffer) != IN::N))
						{
							text += buffer; kol++;
							
							if (kol > STR_MAXSIZE)
								throw ERROR_THROW(115);
						}
						else if (ine(buffer) == IN::Q)
							text += buffer;
						else 
							throw ERROR_THROW(116);
					}
					
					if (file.eof())
						throw ERROR_THROW(117);
					
					buffer = file.get();
				}
				
				if (file.eof())
					break;
				
				switch (ine(buffer))
				{
					case IN::N:
						text += '\n';
						break;
					case IN::F:
						kol_errors++;
						*output_file << "Встречен запрещенный символ для данного участка кода " << buffer << endl;
						cout << "Встречен запрещенный символ для данного участка кода : " << buffer << endl;
						break;
					case IN::G:
					case IN::L:
					case IN::D:
					case IN::A:
					case IN::E:
						text += buffer;
						break;
				}
			}
		}
		
		kol_lines = 0;
		
		for (unsigned int i = 0; i < text.length(); i++)
			if (text[i] == '\n')
				kol_lines++;
		
		if (kol_errors > 0)
			throw ERROR_THROW((int)119);
	}
};