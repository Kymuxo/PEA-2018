#include "stdafx.h"
#include "Mfst.h"
#include "ERROR.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "traccing.h"



#define N__ "---------------------------------------------------------------------------------------\n"


std::ofstream *for_log;

namespace MFST
{
	MfstState::MfstState(int pposition, MFSTSTACK pst, int pnrule, int pnrulechain) : lenta_position(pposition), nrule(pnrule), nrulechain(pnrulechain), st(pst) {};
	
	MfstState::MfstState() 
	{
		lenta_position = 0;	
		nrulechain = -1;	
		nrule = -1; 
	};
	
	Mfst::MfstDiagnosis::MfstDiagnosis(int plenta_position, RC_STEP prc_step, int pnrule, int pnrule_chain)		//	���������� �������� (������)
	{
		lenta_position = plenta_position;		
		rc_step = prc_step;
		
		nrule_chain = pnrule_chain;				
		nrule = pnrule;
	};
	
	Mfst::MfstDiagnosis::MfstDiagnosis()																		//	����������� ��� ������
	{
		lenta_position = nrule_chain = nrule = -1;
		rc_step = START;
	};
	
	Mfst::Mfst(LT::LexTable plex, GRB::Greibach pgrebach, std::ofstream& buff)									// ����������� �� ���������, � �����������
	{
		lex = plex;
		grebach = pgrebach;
		nrule = -1;
		lenta = new int[lex.size];
		lenta_size = lex.size;
		
		for (int i = 0; i < lenta_size; i++)	
			lenta[i] = int(lex.table[i].lexema);
		
		lenta_position = 0;
		st.push(grebach.stbottomT);
		st.push(grebach.startN);
		nrulechain = -1;
		for_log = &buff;
	};
	
	char* Mfst::getCSt(char* buf)																				//	��������� ���� ������� �� ���������� ���� � ����������
	{
		for (int i = st.size() - 1, j = 0; i >= 0; --i, j++)
		{
			buf[j] = GRB::Rule::Chain::alphabet_to_char(st._Get_container()[i]);
		}
		
		buf[st.size()] = '\0';
		
		return buf;
	};
	
	char* Mfst::getCLenta(char* buf, int pos, int n)
	{
		short j = 0;
		int y;
		y = (pos + n) < lenta_size ? (pos + n) : lenta_size;
		
		for (short i = pos; i < y; i++, j++)
		{
			buf[j] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);
		}
		
		buf[j] = 0x00;
		
		return buf;
	}
	
	void Mfst::saveState()																						//	��������� ���������
	{
		storestate.push(MfstState(lenta_position, st, nrule, nrulechain));										//	��������� ������� ��������� ��� � ���� ��
		MFST_TRACE6("SAVESTATE: ", storestate.size());															//	������� ����� ������������ ���������
	};
	
	void Mfst::push_chain(GRB::Rule::Chain chain)																//  �������� ������� � ����
	{
		for (int i = chain.size - 1; i >= 0; i--)	
			st.push(chain.nt[i]);
	};
	
	bool Mfst::reststate()		//����� �� ��������� �����, ���� �� ����� ������ ������������ �, ���� �� ��� ���, ���������� false, ��� ��������������� � ��������� �������
	{

		MfstState tmp;
		
		if (!storestate.empty())
		{
			tmp = storestate.top();
			nrule = tmp.nrule;
			lenta_position = tmp.lenta_position;
			nrulechain = tmp.nrulechain;
			st = tmp.st;
			storestate.pop();
			MFST_TRACE5("RESTATE")
				MFST_TRACE2
		}
		else
			return false;
		return true;
	};
	
	void Mfst::savediagnosis(RC_STEP pprc_step)	//	�������� ������, ��������� ������� �, ���� ������� ������ ��������, �� ��������, ����� ������ �� �������
	{
		int t = 0;
		
		while (t < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[t].lenta_position)
			t++;
		
		if (t < MFST_DIAGN_NUMBER)
		{
			diagnosis[t] = MfstDiagnosis(lenta_position, pprc_step, nrule, nrulechain);
			
			for (int j = t + 1; j < MFST_DIAGN_NUMBER; j++)
				diagnosis[j].lenta_position = -1;
		}
	};
	
	char* Mfst::getDiagnosis(int n, char* buf)	//������� ������ ��� ������� n
	{
		int errid = 0;
		int lpos = -1;

		if (n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0)
		{
			if (lex.table[lpos].line_code > -1)
			{
				errid = grebach.getRule(diagnosis[n].nrule).iderror;
				Error::ERROR err = Error::geterror(errid);
				sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: ������ %d, %s", err.id, lex.table[lpos].line_code, err.message);
			}
		}

		return buf;
	};
	
	void Mfst::printrules()																				//	����� ���������(�� ��������) ������ �������
	{
		MfstState state;
		GRB::Rule rule;
		OUTPUT_STRING("\n������ �������\n")
			for (unsigned int k = 0; k < storestate.size(); k++)
			{
				state = storestate._Get_container()[k];
				rule = grebach.getRule(state.nrule);
				MFST_TRACE7
			}
	};
	
	void Mfst::savededucation()																			//	���������� ���������
	{
		MfstState state;
		GRB::Rule rule;
		deducation.nrules = new int[deducation.size = storestate.size()];
		deducation.nrulechains = new int[deducation.size];
		
		for (unsigned int k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			deducation.nrules[k] = state.nrule;
			deducation.nrulechains[k] = state.nrulechain;
		}
	};
	
	Mfst::RC_STEP Mfst::step()		//�������� ����� �� ������� ��� �� ���������� ������� � ���� �� ����� �� ��������� ������� �����
	{
		if (lenta_position < lenta_size)
		{
			if (st.top() < 0)																			//	if ����������
			{
				GRB::Rule rule;
				
				if ((nrule = grebach.getRule(st.top(), rule)) >= 0)										//	����� ������� ��� ����� �����������
				{
					GRB::Rule::Chain chain;
					
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)
					{
						MFST_TRACE1
							saveState();
						st.pop();
						push_chain(chain);
						MFST_TRACE2
							return NS_OK;
					}
					else
					{
						MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE")
							savediagnosis(NS_NORULECHAIN);
						
						return reststate() ? NS_NORULECHAIN : NS_NORULE;
					}
				}
				else
				{
					return NS_ERROR;
				}
			}
			else if ((st.top() == lenta[lenta_position]))												//	if lexems on lenta and in stack equally
			{
				lenta_position++;
				st.pop();
				nrulechain = -1;
				MFST_TRACE3
					return TS_OK;
			}
			else
			{
				MFST_TRACE4("TS_NOK/NS_NORULECHAIN")
					return reststate() ? TS_NOK : NS_NORULECHAIN;
			}
		}
		else
		{
			MFST_TRACE4("LENTA_END")
				return LENTA_END;
		}
		
		return START;
	};
	
	void Mfst::start()																					//	������� ������ ��������������� �������
	{
		bool rc = false;																				//	����
		MFST_TRACE_START
			RC_STEP rc_step = START;																	//	�������� �� ����
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step();																				//	������ 1�� ����
		
		while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK)
		{
			rc_step = step();																			//	�������� ������ ��� ����� ������ �� �����
		}
		
		switch (rc_step)
		{
			case LENTA_END:																				//	����� �����
				MFST_TRACE4("--------->LENTA_END");
				OUTPUT_STRING(N__)
					sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: ����� ����� %d, �������������� ������ �������� ��� ������", 0, lenta_size);
				OUTPUT_STRING(setw(4) << left << 0 << ": ����� ����� " << lenta_size << ", �������������� ������ �������� ��� ������\n")
					rc = true;
				break;
			case NS_NORULE:
			{
				OUTPUT_STRING("NS_NORULE\n");															//	��� ���������� ������
				
				for (int jk = 0; jk < MFST_DIAGN_NUMBER; jk++)
				{
					OUTPUT_STRING(getDiagnosis(jk, buf) << endl);										//	����� MFST_DIAGN_NUMBER ����������� ������ �������� �������� �� ������
				}
				
				throw Error::geterror(610);
				break;
			}
			case NS_NORULECHAIN:	
				OUTPUT_STRING("NS_NORULECHAIN") 
				break;
			case NS_ERROR:			
				OUTPUT_STRING("NS_ERROR")	
				break;
			case START:				
				OUTPUT_STRING("SURPRISE")		
				break;
		}
	}
}