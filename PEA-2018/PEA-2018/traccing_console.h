#define endl std::endl
#define cout std::cout
#define left std::left
#define setw std::setw
//this file was created to debug with console and defines of traccing not used in main solve
#define LEFT_SIZE 10
//����� ���������� �� ���������
#define MIDDLE_SIZE 30
//���������
#define RIGHT_SIZE 30
#define START_CONSOLE						cout<<setw(LEFT_SIZE)<<left<<"���"<<":"<<\
											setw(MIDDLE_SIZE)<<left<<" �������"<<\
											setw(RIGHT_SIZE)<<left<<" ������� �����"<<\
											setw(MIDDLE_SIZE)<<left<<" ����"<<endl; 
#define TRACE1_CONSOLE						cout << setw(LEFT_SIZE) << left << ++FST_TRACE_n<<": "\
											<< setw(MIDDLE_SIZE) << left << rule.getCRule(rbuf, nrulechain)\
											<< setw(RIGHT_SIZE) << left << MFST::Mfst::getCLenta(lbuf, lenta_position)\
											<< setw(MIDDLE_SIZE) << left << MFST::Mfst::getCSt(sbuf)\
											<< endl;
#define TRACE2_CONSOLE						cout << setw(LEFT_SIZE) << left << FST_TRACE_n << ": "\
											<< setw(MIDDLE_SIZE) << left <<" " \
											<< setw(RIGHT_SIZE) << left << MFST::Mfst::getCLenta(lbuf, lenta_position)\
											<< setw(MIDDLE_SIZE) << left << MFST::Mfst::getCSt(sbuf)\
											<< endl; 
#define TRACE3_CONSOLE						cout << setw(LEFT_SIZE) << left << ++FST_TRACE_n << ": "\
											<< setw(MIDDLE_SIZE) << left << " "\
											<< setw(RIGHT_SIZE) << left << MFST::Mfst::getCLenta(lbuf, lenta_position)\
											<< setw(MIDDLE_SIZE) << left << MFST::Mfst::getCSt(sbuf)\
											<< endl;
