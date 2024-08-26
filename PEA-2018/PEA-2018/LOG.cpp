#include "stdafx.h"
#include "LOG.h"



void LOG::getlog(PARMS parm)
{
	this->stream_for_log = new std::ofstream;
	this->stream_for_log->open(parm.log);
	
	if (!this->stream_for_log)
	{
		throw ERROR_THROW(112);
	}
	
	this->stream_for_out = new std::ofstream;
	this->stream_for_out->open(parm.out);
	
	if (!this->stream_for_out)
	{
		throw ERROR_THROW(111);
	}
}

void LOG::WriteLine(std::string c, ofstream& stream)
{
	stream << c;
}

void LOG::WriteLine(wchar_t* buffer, ofstream& stream)
{
	int i = 0;
	
	while (buffer[i] != L'\0')
	{
		stream << buffer;
		i++;
	}
}

void LOG::WriteLine(char* buffer, ofstream& stream)
{
	stream << buffer;
}

void LOG::WriteLine(char buffer, ofstream& stream)
{
	stream << buffer;
}

void LOG::WriteLog()
{
	char buffer[PARM_MAX_SIZE];

	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	this->WriteLine("\n", (*stream_for_log));
	strftime(buffer, PARM_MAX_SIZE, "Дата: %d.%m.%y", timeinfo);
	this->WriteLine("\n  ---- Протокол ---- \n", (*stream_for_log));
	this->WriteLine(buffer, (*stream_for_log));
	strftime(buffer, PARM_MAX_SIZE, "Время: %H:%M:%S", timeinfo);

	this->WriteLine("\n", (*stream_for_log));
	this->WriteLine(buffer, (*stream_for_log));
	this->WriteLine("\n", (*stream_for_log));
}

void LOG::WriteParm(PARMS parm)
{
	char inInfo[PARM_MAX_SIZE];
	wcstombs(inInfo, parm.in, sizeof(inInfo));
	this->WriteLine("\n ---- Параметры ---- \n -in: \t\t", (*stream_for_log));
	this->WriteLine(inInfo, (*stream_for_log));
	this->WriteLine("\n -out: \t\tfor_out.asm\n -log: \t\tfor_log.txt\n", (*stream_for_log));
}

void LOG::WriteIn(IN in)
{
	this->WriteLine("\n---- Исходные данные ---- \nВсего допустимых символов: " + to_string(in.text.length()) + "\nЗапрещенных символов: \t" + 
		to_string(in.kol_errors) + "\nВсего строк: \t" + to_string(in.kol_lines) + "\n\n", (*stream_for_log));
}

void LOG::WriteError(Error::ERROR e)
{
	this->WriteLine("Ошибка " + to_string(e.id) + ": " + e.message + "\n", (*stream_for_log));
	cout << "Ошибка " << e.id << ": " << e.message << endl;
	
	if (e.line != -1)
	{
		this->WriteLine("line = " + to_string(e.line) + "\n", (*stream_for_log));
		cout << "line = " << e.line << endl;
	}
	
	if (e.id_error != "")
		this->WriteLine("Ошибка в программе связана с идентификатором: " + e.id_error + "\n", (*this->stream_for_log));
}

void LOG::Close()
{
	(*stream_for_log).close();
	(*stream_for_out).close();
}

