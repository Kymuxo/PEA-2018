#include "stdafx.h"
#include "Generic_code.h"



using namespace GC;
using namespace std;


string my_string = FUNCTION_ENDS_ERRORS;

string GC::generic_code(LT::LexTable lextable, IT::IdTable idtable)
{
	string buffer = CODE;
	string end = "";
	bool check_on_string_function = false;

	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_FUNCTION)
		{
			int number = lextable.table[i + 1].number_in_id + 1;

			if (idtable.table[lextable.table[i + 1].number_in_id].iddatatype == IT::STR)
				check_on_string_function = true;

			i++;
			buffer += PROC(idtable.table[lextable.table[i].number_in_id].id);
			int jj = number;
			end = ENDP(idtable.table[lextable.table[i].number_in_id].id);
			buffer += uses;

			for (i++; lextable.table[i].lexema != LEX_RIGHT_BRACKET; i++)
			{
				if (lextable.table[i].lexema == LEX_ID)
				{
					buffer += ", ";
					buffer += idtable.table[lextable.table[i].number_in_id].id + " : " + ASM_INTEGER;
					buffer += "\t";
				}
			}

			buffer += "\n";

			for (; number < idtable.size && idtable.table[number].idtype == IT::P; number++);
			for (number = number - 1; number < idtable.size; number++)
			{
				if (idtable.table[number].idtype == IT::F && idtable.table[number].visibility_area != FLAG_ST_F)
					break;

				if (idtable.table[number].idtype == IT::V)
				{
					if (idtable.table[number].iddatatype == IT::INT)
						buffer = buffer + "mov " + idtable.table[number].id + ", 0\n";

					if (idtable.table[number].iddatatype == IT::STR)
					{
						buffer = buffer + PUSH_(idtable.table[number]);
						buffer = buffer + "push offset " + name_buffer_for_NULL_string + "\n";
						buffer += CALL_COPY_STRING;
					}
				}
			}

			while (idtable.table[jj].idtype == IT::P)
				buffer += "mov eax, " + idtable.table[jj++].id + "\n";

			string buff2 = "";
			buff2 += my_string;
			buff2 += RETURN;
			end = buff2 + end;
			buff2 = "";
		}

		if (lextable.table[i].lexema == LEX_RECOVERY)
		{
			if (check_on_string_function == true)
			{
				check_on_string_function = false;
				int index = lextable.table[i + 1].number_in_id;
				buffer = buffer + PUSH_STR(name_buffer);
				buffer += PUSH_(idtable.table[index]);
				buffer += CALL_COPY_STRING;
			}
			else buffer += MOV_EDX(idtable.table[lextable.table[i + 1].number_in_id].id);
			i += 2;

			continue;
		}

		if (lextable.table[i].lexema == LEX_OUTPUT)
		{
			if (lextable.table[i + 1].lexema == LEX_SEMICOLON)
			{
				buffer += "call new_str\n";
				i++;

				continue;
			}

			buffer += PUSH_(idtable.table[lextable.table[i + 1].number_in_id]);

			if (idtable.table[lextable.table[i + 1].number_in_id].iddatatype == IT::INT)
				buffer += "call write_int\n";
			else buffer += "call write_str\n";
		}

		if (lextable.table[i].lexema == LEX_BEGIN)
		{
			buffer = buffer + PROC("main") + "\n";
			buffer += "push offset consolename\ncall SetConsoleTitleA\n";
			end += MAIN_END;
		}

		if (lextable.table[i].lexema == NULL)
			while (lextable.table[i + 1].lexema == NULL)
				i++;

		if (lextable.table[i].lexema == LEX_END_PROGRAMM_BLOCK)
		{
			buffer += end;
			end = "";
		}

		if (lextable.table[i].lexema == LEX_STANDART_FUNCTION)
			while (lextable.table[i].lexema != LEX_SEMICOLON)
				i++;

		if (lextable.table[i].lexema == LEX_ID && lextable.table[i + 1].lexema == LEX_EQUALITY && idtable.table[lextable.table[i].number_in_id].iddatatype == IT::INT)	
		{																			//	identificator=expression
			int start = i;
			i += 2;

			while (lextable.table[i].lexema != LEX_SEMICOLON)
			{
				if ((lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL) && lextable.table[i + 1].lexema != '[')
					buffer += PUSH_(idtable.table[lextable.table[i].number_in_id]);

				if (lextable.table[i].lexema == LEX_ID && lextable.table[i + 1].lexema == '[')
				{
					int number_id_function = i;

					while (lextable.table[i++].lexema != ']');
						int number_last_args_function = i - 2;

					for (int j = number_last_args_function; j > number_id_function + 1; j -= 1)
						buffer += PUSH_(idtable.table[lextable.table[j].number_in_id]);

					buffer += CALL(idtable.table[lextable.table[number_id_function].number_in_id].id);

					if (idtable.table[lextable.table[number_id_function].number_in_id].visibility_area != FLAG_ST_F)
						buffer += PUSH_EDX;

					if (idtable.table[lextable.table[number_id_function].number_in_id].visibility_area == FLAG_ST_F)
						buffer += PUSH_EAX;

					i--;
				}

				if (lextable.table[i].lexema == LEX_SUMM)
				{
					buffer += POP_ECX;
					buffer += POP_EDX;
					buffer += ADD_ECX_EDX;
					buffer += CHECK_ON_ZAP;
					buffer += PUSH_ECX;
				}

				if (lextable.table[i].lexema == LEX_DIFFERENCE)
				{
					buffer += POP_EDX;
					buffer += POP_ECX;
					buffer += SUB_ECX_EDX;
					buffer += CHECK_ON_ZAP;
					buffer += PUSH_ECX;
				}

				if (lextable.table[i].lexema == LEX_MULTIPLICATION)
				{
					buffer += POP_ECX;
					buffer += POP_EDX;
					buffer += IMUL_ECX_EDX;
					buffer += CHECK_ON_ZAP;
					buffer += PUSH_ECX;
				}

				if (lextable.table[i].lexema == LEX_DIVISION)
				{
					buffer = buffer + POP_ECX;
					buffer = buffer + POP_EAX;
					buffer += "test ecx, ecx\n jz EXIT_div_on_NULL\n";
					buffer += CDQ;
					buffer = buffer + "IDIV " + "ecx" + "\n";
					buffer = buffer + "push eax\n";
				}

				i++;
			}

			buffer = buffer + "pop " + idtable.table[lextable.table[start].number_in_id].id + "\n";
		}

		if (lextable.table[i].lexema == LEX_ID && lextable.table[i + 1].lexema == LEX_EQUALITY && lextable.table[i + 3].lexema == '[' && idtable.table[lextable.table[i].number_in_id].iddatatype == IT::STR)	
		{																					//i=i[];
			int start = i;
			i += 2;
			string end_ = "";

			if (idtable.table[lextable.table[start + 2].number_in_id].id == NAME_STANDART_F_concat || idtable.table[lextable.table[start + 2].number_in_id].id == NAME_STANDART_F_strsub)
			{
				buffer = buffer + PUSH_STR(name_buffer);
			}

			i += 2;

			while (lextable.table[i].lexema != ']')
			{
				end_ = PUSH_(idtable.table[lextable.table[i].number_in_id]) + end_;
				i++;
			}

			buffer += end_;
			buffer += CALL(idtable.table[lextable.table[start + 2].number_in_id].id);
			
			if (idtable.table[lextable.table[start + 2].number_in_id].visibility_area == FLAG_ST_F)
			{
				if (idtable.table[lextable.table[start + 2].number_in_id].id == NAME_STANDART_F_strsub)
					buffer += "cmp eax, -1\nje EXITstrsuberror\n";

				if (idtable.table[lextable.table[start + 2].number_in_id].id == NAME_STANDART_F_concat)
					buffer += "cmp eax, -1\nje EXITconcaterror\n";
			}

			buffer += PUSH_(idtable.table[lextable.table[start].number_in_id]);
			buffer = buffer + PUSH_STR(name_buffer);
			buffer += CALL_COPY_STRING;

			continue;
		}

		if (lextable.table[i].lexema == LEX_ID && lextable.table[i + 1].lexema == LEX_EQUALITY && lextable.table[i + 3].lexema == LEX_SEMICOLON && idtable.table[lextable.table[i].number_in_id].iddatatype == IT::STR)	
		{																						//i=i;
			buffer += PUSH_(idtable.table[lextable.table[i].number_in_id]);
			buffer += PUSH_(idtable.table[lextable.table[i + 2].number_in_id]);
			buffer += CALL_COPY_STRING;
			i += 3;
		}
	}

	return buffer;
}

string GC::generic_data_const(IT::IdTable idtable)
{
	string buffer_data = ".data\n";
	buffer_data = buffer_data + name_buffer_for_NULL_string + ASM_STRING + to_string(STR_MAXSIZE + 1) + " dup(0)\n";
	buffer_data = buffer_data + name_buffer + " " + ASM_STRING + to_string(STR_MAXSIZE + 1) + " dup(0)\t\t; буфер возврата строки из функции\n";
	string buffer_const = ".const\n";
	buffer_const += "consolename db 'PEA-2018',0	;	CONSOLE NAME\n";
	buffer_const += "ZAP_registers___ byte 'ERROR on size of variable', 0\n";
	buffer_const += "ERROR_DIV_NULL byte 'ERROR IN DIVISION(NULL)', 0\n";
	buffer_const += "ERROR_function_strsub byte 'ERROR IN function strsub', 0\n";
	buffer_const += "ERROR_function_concat byte 'ERROR IN function concat', 0\n";
	
	int gg = 0;

	for (int i = 0; i < idtable.size; i++)
	{
		if (idtable.table[i].idtype == IT::L)
		{
			if (idtable.table[i].iddatatype == IT::STR)
			{
				buffer_const += idtable.table[i].id;

				if (idtable.table[i].id.length() < 4)
					buffer_const += "\t";

				if (idtable.table[i].id.length() < 8)
					buffer_const += "\t";

				buffer_const = buffer_const + ASM_STRING + "\'" + idtable.table[i].value.vstr + "\', 0\n";
			}
			else if (idtable.table[i].iddatatype == IT::INT)
			{
				buffer_const += idtable.table[i].id;

				if (idtable.table[i].id.length() < 4)
					buffer_const += "\t";

				if (idtable.table[i].id.length() < 8)
					buffer_const += "\t";

				buffer_const = buffer_const + ASM_INTEGER + to_string(idtable.table[i].value.vint) + "\n";
			}
		}

		if (idtable.table[i].idtype == IT::V)
		{
			if (idtable.table[i].iddatatype == IT::STR)
			{
				buffer_data += idtable.table[i].id;

				if (idtable.table[i].id.length() < 4)
					buffer_data += "\t";

				if (idtable.table[i].id.length() < 8)
					buffer_data += "\t";

				buffer_data = buffer_data + ASM_STRING + to_string(STR_MAXSIZE + 1) + " dup(0)\n";
			}
			else if (idtable.table[i].iddatatype == IT::INT)
			{
				buffer_data += idtable.table[i].id;

				if (idtable.table[i].id.length() < 4)
					buffer_data += "\t";

				if (idtable.table[i].id.length() < 8)
					buffer_data += "\t";

				buffer_data = buffer_data + ASM_INTEGER + "0\n";
			}
		}
	}

	return buffer_data + buffer_const + "\n";
}

string GC::PUSH_(IT::Entry entry)
{
	if (entry.iddatatype == IT::INT)
		return PUSH(entry.id);

	if (entry.idtype == IT::P)
		return PUSH(entry.id);

	return PUSH_STR(entry.id);
}

string GC::prototypes_default_lib()
{
	string buffer = "";

	buffer += "copystring_ PROTO : DWORD, :DWORD\n";
	buffer += "strsub  PROTO : DWORD, :SDWORD, :SDWORD, :DWORD\n";
	buffer += "concat  PROTO : DWORD, :DWORD, :DWORD\n";
	buffer += "lenstr  PROTO : DWORD\n";
	buffer += "write_int PROTO : SDWORD\n";
	buffer += "new_str PROTO\n";

	return buffer;
}

string GC::generic_main(LT::LexTable lextable, IT::IdTable idtable, IN in, LOG log)
{
	string main_buffer = "";

	renamed_IT_LT(lextable, idtable, in);
	main_buffer += generic_head_code();
	main_buffer += generic_data_const(idtable);
	main_buffer += generic_code(lextable, idtable);
	log.WriteLine(main_buffer, (*log.stream_for_out));

	return main_buffer;
}

string GC::generic_head_code()
{
	string buffer;

	buffer += ".586\n";
	buffer += ".model flat, stdcall\n";
	buffer += "includelib libucrt.lib\n";
	buffer += "includelib kernel32.lib\n";
	buffer += "includelib LIB.lib\n";
	buffer += "SetConsoleTitleA PROTO :DWORD\n";
	buffer += "ExitProcess PROTO : SDWORD\t\n";
	buffer += "GetStdHandle     PROTO : DWORD; получить handle вывода на консоль	  \n";
	buffer += "WriteConsoleA    PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD\n";
	buffer += prototypes_default_lib();
	buffer += "";

	return buffer;
}

void GC::renamed_IT_LT(LT::LexTable &lextable, IT::IdTable &idtable, IN in)
{
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_SIGN)
			lextable.table[i].lexema = in.text[lextable.table[i].number_in_input];

	for (int i = 0; i < idtable.size; i++)
		if ((idtable.table[i].idtype == IT::V || idtable.table[i].idtype == IT::P) && idtable.table[i].visibility_area != FLAG_ST_F)
			idtable.table[i].id += "_" + idtable.table[i].visibility_area;

	for (int i = 0; i < idtable.size; i++)
		if (idtable.table[i].idtype == IT::V || idtable.table[i].idtype == IT::P)
			idtable.table[i].id += "_" + to_string(i);
}

string GC::generic_end_main()
{
	string buffer = "";
	buffer += my_string;

	buffer += "push 0\ncall ExitProcess\t\t; завершение процесса Windows\nmain ENDP\n\n";

	buffer += "write_str PROC uses eax ebx ecx edi esi, pstr: SDWORD\n";
	buffer += "push - 11\t\t; -11 - handle для стандартного вывода\n";
	buffer += "call GetStdHandle\n";
	buffer += "mov esi, pstr\t; подсчет количества  цикл пока не нулевой символ и считать так количество символов\n";
	buffer += "mov edi, -1\t\t; символов(до 0h)\n";
	buffer += "count:\t\t; в выводимой\n";
	buffer += "inc edi\t\t; на консоль строке\n";
	buffer += "cmp byte ptr[esi + edi], 0\n";
	buffer += "jne count; количество символов->edi\n";
	buffer += "push 0\n";
	buffer += "push 0\n";
	buffer += "push edi\n";
	buffer += "push pstr\t\t; адрес выводимой строки\n";
	buffer += "push eax\t\t; handle для вывода\n";
	buffer += "call WriteConsoleA\t; вывести на консоль\n";
	buffer += "ret\n";
	buffer += "write_str ENDP\n";

	buffer += "end main";

	return buffer;
}