#pragma once

#include "traccing_console.h"				//	Прописаны максроы для вывода разбора на консоль	+ define на вывод



int FST_TRACE_n = -1;

char rbuf[205], sbuf[205], lbuf[1024];		//205 205 1024


#define MFST_TRACE_START					/*START_CONSOLE*/\
											*for_log<<setw(LEFT_SIZE)<<left<<"Шаг"<<":"<<\
											setw(MIDDLE_SIZE) << left << " Правило" << \
											setw(RIGHT_SIZE) << left << " Входная лента" << \
											setw(MIDDLE_SIZE) << left << " Стек" << endl;


#define MFST_TRACE1							/*TRACE1_CONSOLE*/\
											*for_log << setw(LEFT_SIZE) << left << ++FST_TRACE_n << ": "\
											<< setw(MIDDLE_SIZE) << left << rule.getCRule(rbuf, nrulechain)\
											<< setw(RIGHT_SIZE) << left << MFST::Mfst::getCLenta(lbuf, lenta_position)\
											<< setw(MIDDLE_SIZE) << left << MFST::Mfst::getCSt(sbuf)\
											<< endl;


#define MFST_TRACE2							/*TRACE2_CONSOLE*/\
											*for_log << setw(LEFT_SIZE) << left << FST_TRACE_n << ": "\
											<< setw(MIDDLE_SIZE) << left << " " \
											<< setw(RIGHT_SIZE) << left << MFST::Mfst::getCLenta(lbuf, lenta_position)\
											<< setw(MIDDLE_SIZE) << left << MFST::Mfst::getCSt(sbuf)\
											<< endl;

#define MFST_TRACE3							/*TRACE3_CONSOLE*/\
											*for_log << setw(LEFT_SIZE) << left << ++FST_TRACE_n << ": "\
											<< setw(MIDDLE_SIZE) << left << " "\
											<< setw(RIGHT_SIZE) << left << MFST::Mfst::getCLenta(lbuf, lenta_position)\
											<< setw(MIDDLE_SIZE) << left << MFST::Mfst::getCSt(sbuf)\
											<< endl;

#define MFST_TRACE4(c)						/*cout << setw(LEFT_SIZE) << left << ++FST_TRACE_n << ": " <<setw(MIDDLE_SIZE)<<left<<c<<endl;*/\
											*for_log << setw(LEFT_SIZE) << left << ++FST_TRACE_n << ": " << setw(MIDDLE_SIZE) << left << c << endl;

#define MFST_TRACE5(c)						/*cout << setw(LEFT_SIZE) << left << FST_TRACE_n << ": "<<setw(MIDDLE_SIZE)<<left<<c<<endl;*/\
											*for_log << setw(LEFT_SIZE) << left << FST_TRACE_n << ": " << setw(MIDDLE_SIZE) << left << c << endl;

#define MFST_TRACE6(c, k)					/*cout << setw(LEFT_SIZE) << left << FST_TRACE_n << ": "<<setw(MIDDLE_SIZE)<<left<<c<<k<<endl;*/\
											*for_log << setw(LEFT_SIZE) << left << FST_TRACE_n << ": " << setw(MIDDLE_SIZE) << left << c << k << endl;

#define MFST_TRACE7							/*cout << setw(LEFT_SIZE) << left << state.lenta_position << ": "\
									  												<< setw(MIDDLE_SIZE) << left << rule.getCRule(rbuf, state.nrulechain)\
									  																							<< endl;*/\
											*for_log << setw(LEFT_SIZE) << left << state.lenta_position << ": "\
											<< setw(MIDDLE_SIZE) << left << rule.getCRule(rbuf, state.nrulechain)\
											<< endl;

#define OUTPUT_STRING(c)					/*cout<<c;*/ *for_log << c;
