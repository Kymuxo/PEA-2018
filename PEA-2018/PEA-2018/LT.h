#pragma once

#define LT_MAXSIZE					100000 //максимальный размер таблицы лексем


namespace LT
{
	struct Entry
	{
		char lexema;
		int line_code;
		int number_in_id = -1;
		int number_in_input = -1;
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	void check_on_zap_LT(LexTable & lextable);
}
