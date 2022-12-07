#include "ColliderColorChanger.h"

void ColliderColorChange::ChangeColor()
{
	if (isColliding)
	{
		activeColor = SDL_Color{0, 0, 255};
	}
	else
	{
		activeColor = defaultColor;
	}
}