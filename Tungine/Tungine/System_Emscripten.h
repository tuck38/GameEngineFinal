#pragma once
#include "System_Common.h"
#include <emscripten.h>
#include "SDL2/SDL.h"

namespace Tungine
{

	const Tungine::string error = "do not press k!";
	const Tungine::string errorGameObject = "Too many game objects";

	class System_Emscripten : public System
	{

		

	public:

		void Init() override;

		void Shutdown() override;

		void ShowError(const Tungine::string& message) override;

		void LogToErrorFile(const Tungine::string& message) override;
	};
}
