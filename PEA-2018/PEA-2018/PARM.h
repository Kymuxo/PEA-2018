#pragma once

#include "ERROR.h"



#define PARM_IN L"-in:"
#define PARM_MAX_SIZE 100
#define PARM_OUT_STANDART		L"..\\..\\ASM_TESTER\\ASM_TESTER\\tester.asm" //L"for_out.asm"
#define PARM_LOG_STANDART		L"for_log.txt"


class PARMS
{
	public:
		wchar_t in[PARM_MAX_SIZE];
		wchar_t out[sizeof(PARM_OUT_STANDART) / 2 + 1];
		wchar_t log[sizeof(PARM_LOG_STANDART) / 2 + 1];

		void getparm(int argc, wchar_t* argv[]);
};
