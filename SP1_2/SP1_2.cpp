#define  _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");

	char mod[3];
	/*if (argc != 2) {
		printf("Error: found %d arguments. Needs 1", argc - 1);
		exit(1);
	}
	strcpy(mod, argv[1]);
	/*
		Преобразование в Unicode
	*/
	//if (strcmp(mod, "-u") == 0) {
		ifstream in("text.txt");
		string line, all_text="";
		
		if (in.is_open())
		{
			while (getline(in, line))
			{
				//std::cout << line << std::endl;
				all_text += line;
			}
		}
		in.close(); // закрываем файл
		int kol = all_text.length();
		char *alt;
		alt = (char*)malloc(kol * sizeof(int) + 1);
		strcpy(alt, all_text.c_str());
		//int iRes = WideCharToMultiByte(CP_ACP, 0, alt, -1, pcb, length, 0, 0);

	//}
	system("pause");
	
	return 0;
}