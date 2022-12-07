#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include "SDL.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "System_Common.h"
#include <sstream>
namespace Tungine
{

	const Tungine::string error = L"do not press k!";
	const Tungine::string errorGameObject = L"Too many game objects";

	


	class System_Win32 : public System
	{

	public:

		void Init() override;

		void Shutdown() override;

		void ShowError(const Tungine::string& message) override;

		void LogToErrorFile(const Tungine::string& message) override;

		HANDLE file;
	};
}