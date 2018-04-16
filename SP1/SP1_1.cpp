#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <locale.h>

void SetError() {
	LPTSTR pszBuf = NULL;

	pszBuf = (LPTSTR)LocalAlloc(
		LPTR,
		180000000000000000 * sizeof(TCHAR));
}
int main(int argc, char **argv) {
	setlocale(LC_CTYPE, "rus");
	
	char mod[3];
	if (argc != 2) {
		printf("Error: found %d arguments. Needs 1", argc - 1);
		exit(1);
	}
	strcpy(mod, argv[1]);
	if (strcmp(mod, "-e") == 0) {
		// делаем преднамеренно ошибку, при которой не хватит памяти компу
		SetError();
		// получаем код ошибки
		DWORD lastErrorCode = GetLastError();
		printf("GetLastError returned %u\n", lastErrorCode);
		void* cstr; //в эту переменную будет записано сообщение
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR)&cstr,
			0,
			NULL
		);
		// преобразовываем сообщение в читабельный вид
		PTCHAR res((char*)cstr);
		printf("%s", res);
		//освобождаем память
		LocalFree(cstr);
	}
	
	if (strcmp(mod, "-s") == 0) {
		// по всякому измываемся над получением инфы о системе
		MEMORYSTATUS lpBuffer;
		lpBuffer.dwLength = sizeof(lpBuffer);
		GlobalMemoryStatus(&lpBuffer);
		printf("  Процент использования физической памяти : %d %%\n", lpBuffer.dwMemoryLoad);
		printf("  Объем физической памяти : %d (bytes)\n", lpBuffer.dwTotalPhys);
		printf("  Объем доступной физической памяти : %d (bytes)\n", lpBuffer.dwAvailPhys);
		printf("  Max кол-во байт, к-е может содержаться в страничном файле на жестком диске : %u (bytes)\n", lpBuffer.dwTotalPageFile);
		printf("  Max кол-во байт, к-е может быть передано процессу из страничного файла : %u (bytes)\n", lpBuffer.dwAvailPageFile);
		printf("  Кол-во байт в адресном пространстве, принадлежащих лично данному процессу : %d (bytes)\n", lpBuffer.dwTotalVirtual);
		printf("  Oбъем свободных регионов в адресном пространстве процесса,вызывающего процедуру GlobalMemoryStatus : %d (bytes)\n", lpBuffer.dwAvailVirtual);
		SYSTEM_INFO sys;
		GetSystemInfo(&sys);
		// Display the contents of the SYSTEM_INFO structure. 
		printf("Hardware information: \n");
		printf("  OEM ID: %u\n", sys.dwOemId);
		printf("  Number of processors: %u\n",sys.dwNumberOfProcessors);
		printf("  Page size: %u\n", sys.dwPageSize);
		printf("  Processor type: %u\n", sys.dwProcessorType);
		printf("  Minimum application address: %lx\n",sys.lpMinimumApplicationAddress);
		printf("  Maximum application address: %lx\n",sys.lpMaximumApplicationAddress);
		printf("  Active processor mask: %u\n",sys.dwActiveProcessorMask);
	}
	//system("pause");
}