#ifdef __EMSCRIPTEN__
	#include "System_Emscripten.h"
#elif _WIN32
	#include "System_Win32.h"
#endif