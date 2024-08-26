#pragma once

#include <stack>
#include "IN.h"
#include "LT.h"
#include "IT.h"
#include "Output_functions.h"



namespace PN
{
	int priority(char symbol);
	void copy_LT(LT::LexTable& lextable, LT::LexTable& lextable2, int i);
	void Polish_notation_inverse(int &start_position, LT::LexTable& lextable, IT::IdTable& idtable, IN in, LT::LexTable& lextable2);
	void Polish_Notation_main(LT::LexTable& lextable, IT::IdTable& idtable, IN in, LOG log);
};