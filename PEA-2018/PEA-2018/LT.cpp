#include "stdafx.h"
#include "LT.h"
#include "ERROR.h"
#include "ERROR.h"



namespace LT
{
	LexTable Create(int size)												//создание таблицы лексем
	{
		LexTable* New = new LexTable;
		New->maxsize = size;
		New->size = 0;
		New->table = new Entry[size];
		memset(New->table, 0xff, sizeof(Entry)*size);
		
		return *New;
	}

	void Add(LexTable& lextable, Entry entry)								//добавление лексемы
	{
		lextable.table[lextable.size++] = entry;
		check_on_zap_LT(lextable);
	}

	void check_on_zap_LT(LexTable & lextable)
	{
		if (lextable.size == LT_MAXSIZE) 
			throw ERROR_THROW((int)310);
	}
}