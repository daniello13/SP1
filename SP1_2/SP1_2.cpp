#define  _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Convert a wide Unicode string to an UTF8 string
std::string utf8_encode(const std::wstring &wstr)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}
/* 
	Convert an UTF8 string to a wide Unicode String
	Юзаем при переводе из удлиненной кодировки в сокращенную
*/
std::wstring utf8_decode(const std::string &str)
{
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}
int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");
	char mod[3];
	if (argc != 3) {
		printf("Error: found %d arguments. Needs 2", argc - 1);
		exit(1);
	}
	strcpy(mod, argv[1]);
	char* FileName = (char*)malloc(strlen(argv[2])*sizeof(char));
	strcpy(FileName, argv[2]);
	/*
		Преобразование в UTF-8 из OEM 866
		Если файл изначально весил 50 байт, после этого дела он будет весить 100 Б

	*/
	if (strcmp(mod, "-a") == 0) {
		wifstream in(FileName);
		wstring line, all_text;
		in.imbue(locale("rus_rus.866"));
		if (in.is_open())
		{
			while (getline(in, line))
			{
				//std::cout << line << std::endl;
				all_text += line;
			}
		}
		in.close(); // закрываем файл
		string answer = utf8_encode(all_text);
		ofstream fout(FileName, ios::trunc);
		fout.imbue(locale("rus_rus.866"));
		fout << answer;
		fout.close();

		}
		
	/*
		Файл должен быть в кодировке UTF-8
		считывание, преобразование кириллицы в OEM 866
		Если файл изначально весил 100 байт, после этого он будет весить 50 Б
	*/
	
	else if (strcmp(mod, "-u") == 0) {

		ifstream in(FileName);
		string line, all_text = "";

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
		line = (const char*)alt;
		wstring wide = utf8_decode(line);
		wofstream fout(FileName, ios::trunc);
		fout.imbue(locale("rus_rus.866"));
		fout << wide;
		fout.close();
	}
	else {
		cout << "Неверный ключ" << endl;
	}
	return 0;
}