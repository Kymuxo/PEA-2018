#pragma once

#include "stdafx.h"
#include "LT.h"
#include "IT.h"



namespace OF
{
	void output_lexems(LT::LexTable &Lex_Table, LOG log, IN in);
	void Output_identifikators(IT::IdTable &ID_Table, LOG log);
}