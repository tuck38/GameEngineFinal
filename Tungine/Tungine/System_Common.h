#pragma once
#include <stdlib.h>
#include <iostream>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

namespace Tungine
{
	
	#ifdef __EMSCRIPTEN__
		typedef std::string string;
	#elif _WIN32
		typedef std::wstring string;
	#endif

	class System
	{

	public:

		virtual void Init() = 0;

		virtual void Shutdown() = 0;

		virtual void ShowError(const Tungine::string& message) = 0;

		virtual void LogToErrorFile(const Tungine::string& message) = 0;

		static System* Create();
	};
}
