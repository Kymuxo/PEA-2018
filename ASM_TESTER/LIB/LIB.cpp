#include <iostream>
using namespace std;
extern "C"
{
	int _stdcall new_str()
	{

		std::cout << std::endl;
		return 0;
	}
	int _stdcall lenstr(char*string)
	{
		int kol = 0;
		while (string[kol] != '\0')
			kol++;
		return kol;
	};
	int _stdcall concat(char* object1, char* object2, char*object3)
	{
		char buffer[201];

		int size = 0;
		for (int i = 0; object1[i] != '\0'; i++, size++)
		{
			buffer[size] = object1[i];
			if (size > 200)
			{
				buffer[size] = '\0';
				return -1;
			}
		}
		for (int i = 0; object2[i] != '\0'; i++, size++)
		{
			buffer[size] = object2[i];
			if (size > 200)
			{
				buffer[size] = '\0';
				return -1;
			}
		}
		buffer[size] = '\0';
		for (int i = 0; i < size + 1; i++)
			object3[i] = buffer[i];
		return 0;
	};
	int _stdcall write_int(int a)
	{
		cout << a;
		return 0;
	}
	int _stdcall  strsub(char* object, int start, int end, char* object_ret)
	{
		if (start < 1)return -1;
		if (start > end)return -1;
		for (int i = 0;i < start;i++)if (object[i] == '\0') return -1;
		start--;
		for (int i = start;i < end + 1;i++)
		{
			if (object[i] == '\0' && i < end)
			{
				object_ret[i - start] = '\0';
				return -1;
			}
			
			object_ret[i - start] = object[i];
			if (i == end) {
				object_ret[i - start] = '\0';return 0;
			}
		}
		return -1;
	}
	int _stdcall copystring_(char* object1, char* object2)
	{
		int i = 0;
		while (object1[i] != '\0')
		{
			object2[i] = object1[i];
			i++;
		}
		object2[i] = '\0';
		return 0;
	}
};