#include "System_Emscripten.h"

void Tungine::System_Emscripten::Init()
{

}

void Tungine::System_Emscripten::Shutdown()
{
	
}

void Tungine::System_Emscripten::ShowError(const Tungine::string& message)
{
	emscripten_run_script("alert('message')");
}

void Tungine::System_Emscripten::LogToErrorFile(const Tungine::string& message)
{
	emscripten_run_script("throw 'message'");
}

Tungine::System* Tungine::System::Create()
{
	return DBG_NEW System_Emscripten();
}