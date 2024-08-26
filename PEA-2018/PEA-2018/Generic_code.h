#pragma once

#include "stdafx.h"
#include "IT.h"
#include "LT.h"
#include "IN.h"



#define uses							"\tuses eax ebx ecx edi esi"	
#define ASM_STRING						" byte "
#define ASM_INTEGER						" SDWORD "
#define PUSH(a)							"push\t" + a + "\n"
#define PUSH_STR(a)						"push\toffset\t" + a + "\n"
#define CALL(a)							"call\t" + a + "\n"
#define POP_EAX							"pop\teax\n"
#define POP_ECX							"pop\tecx\n"
#define POP_EDX							"pop\tedx\n"
#define ADD_ECX_EDX						"add\tecx,\tedx\n"
#define PUSH_ECX						"push\tecx\n"
#define PUSH_EDX						"push\tedx\n"
#define PUSH_EAX						"push\teax\n"
#define SUB_ECX_EDX						"sub\tecx,\tedx\n"
#define IMUL_ECX_EDX					"imul\tecx,\tedx\n"
#define CDQ								"cdq\n"
#define name_buffer_for_division		"buffer_SDWORD_for_division"
#define CALL_COPY_STRING				"call\tcopystring_\n"
#define name_buffer						"buffer_string_for_return"
#define RETURN							"ret 0\n"
#define PROC(a)							"\t" + a + "\tPROC"
#define ENDP(a)							"\t" + a + "\tENDP\n"
#define name_buffer_for_NULL_string		"name_buffer_for_NULL_string"
#define MOV_EDX(a)						"mov\tedx,\t" + a + "\n"
#define CHECK_ON_ZAP					"jo ZAP_registers__\n"
#define MAIN_END						GC::generic_end_main()
#define FUNCTION_ENDS_ERRORS			"jmp EXIT\nEXIT_div_on_NULL:\npush offset ERROR_DIV_NULL\ncall write_str\npush -1\ncall ExitProcess\nEXITstrsuberror:\npush offset ERROR_function_strsub\ncall write_str\npush -2\ncall ExitProcess\nEXITconcaterror:\npush offset ERROR_function_concat\ncall write_str\npush -3\ncall ExitProcess\nZAP_registers__:\npush offset ZAP_registers___\ncall write_str\npush - 4\ncall ExitProcess\nEXIT:\n"
#define CODE							"\n.code\n"


namespace GC
{
	std::string generic_main(LT::LexTable lextable, IT::IdTable idtable, IN in, LOG log);
	std::string generic_code(LT::LexTable, IT::IdTable);
	std::string prototypes_default_lib();
	std::string generic_head_code();
	std::string PUSH_(IT::Entry entry);
	std::string generic_data_const(IT::IdTable idtable);
	void renamed_IT_LT(LT::LexTable &lextable, IT::IdTable &idtable, IN in);
	std::string generic_end_main();
}