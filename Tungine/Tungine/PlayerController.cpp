#include "PlayerController.h"

bool PlayerController::getInput()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_LEFT])
	{
		transform.move(-moveValue, 0, 0);
		return true;
	}
	else if (keystate[SDL_SCANCODE_RIGHT])
	{
		transform.move(moveValue, 0, 0);
		return true;
	}
	else if (keystate[SDL_SCANCODE_UP])
	{
		transform.move(0, -moveValue, 0);
		return true;
	}
	else if (keystate[SDL_SCANCODE_DOWN])
	{
		transform.move(0, moveValue, 0);
		return true;
	}
	return false;
}