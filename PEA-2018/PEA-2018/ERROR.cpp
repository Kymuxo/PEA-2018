#include "stdafx.h"
#include "ERROR.h"



namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(000, "������������ ��� ������"),
		ERROR_ENTRY(001, "��������� ����"),
		
		ERROR_ENTRY(100, "�������� -in ������ ���� �����"),
		ERROR_ENTRY(105, "��������� ����� �������� ���������"),
		
		ERROR_ENTRY(110, "������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "������ ��� �������� ����� ���� �� ASM (for_out.asm)"),
		ERROR_ENTRY(112, "������ ��� �������� ����� ��������� (for_log.txt)"),

		ERROR_ENTRY(115, "������ ��� ��������� ������ �� ����� : ������� ������� ��������� �������"),
		ERROR_ENTRY(116, "������ ��� ��������� ������ �� ����� : ������������ ������� ������ ������-��������!"),
		ERROR_ENTRY(117, "������ ��� ��������� ������ �� ����� : ���������� ������ ������ ������"),
		ERROR_ENTRY(118, "������ ��� ��������� ������ �� ����� : ��������� ������ ������-�������"),
		ERROR_ENTRY(119, "������ ��� ��������� ������ �� ����� : ������������ ������ � �������� ����"),

		ERROR_ENTRY(300, "���������� ���������� ����� � ������������� ��� � �������"),
		ERROR_ENTRY(311, "������������ ������������ ���������� ��������������� ����: ������� (������ �����������, ��. � ������������)"),
		ERROR_ENTRY(310, "���������� ������� ������ ������� � ������� ������ - ������� ������ �����������!"),
		ERROR_ENTRY(312, "������������ ������������ ���������� ��������������� ����: ������� (������ �����������, ��. � ������������)"),
		ERROR_ENTRY(313, "������������ ������������ ���������� ��������������� ����: ���������� (������ �����������, ��. � ������������)"),
		ERROR_ENTRY(314, "������������ ������������ ���������� ��������������� ����: �������� (������ �����������, ��. � ������������)"),

		ERROR_ENTRY(401, "������������� ������: ������������ ������������� ���������� ���� ������������� �������!"),
		ERROR_ENTRY(402, "������������� ������: ��������� ���������� ���������� � �������"),
		ERROR_ENTRY(403, "������������� ������: �������������� ����� ������, ������������ � �������"),
		ERROR_ENTRY(404, "������������� ������: �������������� ���������� ����������, ������������ � �������"),
		ERROR_ENTRY(405, "������������� ������: �������� ����������� ���������� ���� ���������� ����� ������� � ������ ����������!"),
		ERROR_ENTRY(406, "������������� ������: ������������ �������� ��� ��������!"),
		ERROR_ENTRY(407, "������������� ������: ��� ������������� �������� ������� �� ��������� � �����������!"),
		ERROR_ENTRY(409, "������������� ������: ������������ ���� �������!"),
		ERROR_ENTRY(410, "������������� ������: ������� ������������� �������������� �������� ��� �����! ����������� ������� ����������� ����������"),
		ERROR_ENTRY(411, "������������� ������: ������������� ������������������ �����, ������������� ��� ����������� �������"),
		ERROR_ENTRY(413, "������������� ������: �������������� ����� ������ � ���������!"),
		ERROR_ENTRY(414, "������������� ������: ������� ������������ ��������!"),

		ERROR_ENTRY(600, "�������������� ������: �������� ����������� ���������"),
		ERROR_ENTRY(601, "�������������� ������: ������ � ���������� ������ ���� �������"),
		ERROR_ENTRY(602, "�������������� ������: ������ � ���������� �������"),
		ERROR_ENTRY(603, "�������������� ������: ������ � ��������� (��������, �����*�����/�������)"),
		ERROR_ENTRY(604, "�������������� ������: ������ � �������� ���������� � �������, ��������, (, a)"),
		ERROR_ENTRY(605, "�������������� ������: ������ � ������������ ��������"),
		ERROR_ENTRY(610, "�������������� ������: ������ �� ����� ������ ��������������� �����������!"),

		ERROR_ENTRY(ERROR_MAX_ENTRY,"END_FLAG")
	};

	ERROR geterror(int get_id = -1)													// ������� ������ ������
	{
		if (get_id > 0 && get_id < ERROR_MAX_ENTRY)									//	�������� ������ ������
		{
			for (int i = 0; errors[i].id != ERROR_MAX_ENTRY; i++)
				if (errors[i].id == get_id)
				{
					return errors[i];
				}
		}
		return errors[0];
	}

	ERROR geterrorin(int get_id = -1, int line = -1, std::string id_errors = "")	//	������� ������ � ���������
	{
		if (get_id > 0 && get_id < ERROR_MAX_ENTRY)									//	�������� ������ ������
		{
			for (int i = 0; i < ERROR_MAX_ENTRY; i++)
				if (errors[i].id == get_id)
				{
					errors[i].line = line;
					errors[i].id_error = id_errors;
					return errors[i];
				}
		}
		return errors[0];
	}
}