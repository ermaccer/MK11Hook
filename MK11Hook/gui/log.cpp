#include "log.h"
#include <iostream>
#include <Windows.h>
#include <time.h>

wchar_t eLog::path[MAX_PATH];

void eLog::Initialize()
{
	GetModuleFileNameW(NULL, path, MAX_PATH);

	wchar_t* end = wcsrchr(path, L'\\');
	if (end)
		end[1] = 0x00;
	wcscat(path, LOGNAME);

	FILE* cls = _wfopen(path, L"w");
	fclose(cls);
	FILE* log = _wfopen(path, L"a+");
	time_t ttime = time(0);
	fprintf(log, "Logging Started - %s", ctime(&ttime));
	fclose(log);
}

void eLog::Message(const char* function, const char* format, ...)
{
	char msg[2048];

	va_list args;
	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);

	FILE* log = _wfopen(path, L"a+");

	if (log)
	{
		fprintf(log, "%s | %s\n", function, msg);
		fclose(log);
	}

	printf("%s | %s\n", function, msg);
}

