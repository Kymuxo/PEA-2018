#include "stdafx.h"
#include "PARM.h"



void PARMS::getparm(int argc, wchar_t* argv[])
{
	bool Check_On_In = false;
	wchar_t *buffer = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (wcslen(argv[i]) < PARM_MAX_SIZE)											//wcslen длина строки
		{
			if (wcsstr(argv[i], PARM_IN) != 0)											//wcsstr поиск первой позиции подстркои в строке
			{
				buffer = wcsstr(argv[i], PARM_IN) + wcslen(PARM_IN);

				wcscpy(in, buffer);														// wcscpy копирование
				buffer -= wcslen(PARM_IN);
				Check_On_In = true;
			}
		}
		else
		{
			throw ERROR_THROW(105);
		}
	}
	
	if (!Check_On_In)
		throw ERROR_THROW(100);
	
	wcscpy(out, PARM_OUT_STANDART);
	wcscpy(log, PARM_LOG_STANDART);
}