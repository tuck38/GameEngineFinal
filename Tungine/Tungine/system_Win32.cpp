#include "System_Win32.h"

void Tungine::System_Win32::Init()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	bool console = AllocConsole();

	if (!console)
	{
		ShowError(L"Console failed to open!");
	}

	file = freopen("CONOUT$", "w", stdout);
	file = CreateFileW(L"GameErrors.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

void Tungine::System_Win32::Shutdown()
{
	CloseHandle(file);
}

void Tungine::System_Win32::ShowError(const Tungine::string& message)
{
	MessageBox(NULL, message.c_str(), NULL, MB_ICONERROR | MB_OK);
	LogToErrorFile(message);
}

void Tungine::System_Win32::LogToErrorFile(const Tungine::string& message)
{
	WriteFile(file, message.c_str(), message.size() * sizeof(wchar_t), 0, NULL);
}

Tungine::System* Tungine::System::Create()
{
	return DBG_NEW System_Win32();
}