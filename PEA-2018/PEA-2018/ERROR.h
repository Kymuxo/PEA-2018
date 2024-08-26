#pragma once

#include "stdafx.h"



#define ERROR_THROW(id) Error::geterror(id);
#define ERROR_ENTRY(id, m) {id, m, (-1, -1)}
#define ERROR_MAXSIZE_MESSAGE 200
#define ERROR_MAX_ENTRY 1000


namespace Error
{
	struct ERROR
	{
		int id;
		char message[ERROR_MAXSIZE_MESSAGE];
		int line;
		std::string id_error;
	};

	ERROR geterror(int id);

	ERROR geterrorin(int id, int line, std::string id_errorp);
}