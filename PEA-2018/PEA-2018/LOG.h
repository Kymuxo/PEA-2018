#pragma once

#include "stdafx.h"
#include "IN.h"
#include "PARM.h"
#include "ERROR.h"



class LOG
{
	public:
		wchar_t logfile[PARM_MAX_SIZE];

		std::ofstream *stream_for_log;
		std::ofstream *stream_for_out;

		LOG() :logfile(L""), stream_for_log(NULL), stream_for_out(NULL) {}
		void getlog(PARMS parm);

		void WriteLine(std::string c, ofstream& stream);
		void WriteLine(wchar_t* buffer, ofstream& stream);
		void WriteLine(char* buffer, ofstream& stream);
		void WriteLine(char buffer, ofstream& stream);
		void WriteLog();
		void WriteParm(PARMS parm);
		void WriteIn(IN in);
		void WriteError(Error::ERROR e);
		void Close();
};
