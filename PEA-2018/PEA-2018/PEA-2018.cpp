#include "stdafx.h"
#include "IN.h"
#include "PARM.h"
#include "LOG.h"
#include "LT.h"
#include "IT.h"
#include "PolishNotation.h"
#include "MFST.h"
#include "FST.h"
#include "Output_functions.h"
#include "Generic_code.h"



void semantic_analiz_last_part(LT::LexTable lextable, LOG log, IT::IdTable idtable);
int IN::code[] = IN_CODE_TABLE;
void LexAnaliz(IN in, LOG log, PARMS Parms, LT::LexTable &Lex_Table, IT::IdTable &ID_Table);

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	LOG log;

	try
	{
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(IT_MAX_SIZE);
		PARMS parm;
		parm.getparm(argc, argv);
		
		try
		{
			log.getlog(parm);
			std::string head = "\t\tФайл LOG";
			log.WriteLine(head, (*log.stream_for_log));
			log.WriteLog();
			log.WriteParm(parm);
			IN in;
			cout << "Здесь будет отображен ход выполнения генерации кода" << endl;
			in.getin(parm.in, (log.stream_for_log));
			log.WriteIn(in);
			log.WriteLine("Отформатированный исходный код:\n", (*log.stream_for_log));
			log.WriteLine("\n" + in.text + "\n", (*log.stream_for_log));
			LexAnaliz(in, log, parm, lextable, idtable);
			log.WriteLine("\nЛексический анализ выполнен успешно!\n", (*log.stream_for_log));
			cout << "Лексический анализ выполнен успешно!" << endl;
			OF::output_lexems(lextable, log, in);
			OF::Output_identifikators(idtable, log);
			lextable.table[lextable.size].lexema = '$';
			lextable.table[lextable.size].line_code = lextable.table[lextable.size - 1].line_code;
			lextable.size++;
			MFST::Mfst mfst(lextable, GRB::getGreibach(), (*log.stream_for_log));
			mfst.start();
			mfst.savededucation();
			mfst.printrules();
			cout << "Синтаксический анализ выполнен успешно!\n";
			log.WriteLine("\nСинтаксический анализ выполнен успешно!\n", (*log.stream_for_log));
			lextable.size--;
			semantic_analiz_last_part(lextable, log, idtable);
			PN::Polish_Notation_main(lextable, idtable, in, log);
			GC::generic_main(lextable, idtable, in, log);
			log.WriteLine("Генерация кода прошла успешно! Исходный код, транслированный на Assembler см. в файле for_out.asm", (*log.stream_for_log));
			cout << "Генерация кода прошла успешно! Исходный код, транслированный на Assembler см. в файле for_out.asm\n";
		}
		catch (Error::ERROR e)
		{
			log.WriteError(e);
			cout << "Произошла ошибка в работе программы! Подробнее в файле лога log.txt" << endl;
			system("pause");
		}
		catch (...)
		{
			Error::ERROR e;
			e.line = -1;
			e = Error::geterror(1);
			log.WriteError(e);
			system("pause");
		}
		log.Close();
	}
	catch (Error::ERROR e)
	{
		cout << "Ошибка " << e.id << ": " << e.message << endl;
		if (e.line != -1)
			cout << "line = " << e.line << endl;
		cout << "Произошла ошибка в работе программы!" << endl;
		system("pause");
	}
	catch (...)
	{
		Error::ERROR e;
		e.line = -1;
		e = Error::geterror(1);
		log.WriteError(e);
		system("pause");
	}
	return 0;
}