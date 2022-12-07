#pragma once
#include "RectangleRenderer.h"

class ColliderColorChange
{
public:

	ColliderColorChange()
	{
		isColliding = 0;
		defaultColor = SDL_Color();
		activeColor = defaultColor;
	}

	ColliderColorChange(SDL_Color dc)
	{
		isColliding = false;
		defaultColor = dc;
		activeColor = defaultColor;
	}

	void ChangeColor();

	SDL_Color &getActiveColor()
	{
		return activeColor;
	}

	bool getState()
	{
		return isColliding;
	}

	void setState(bool &state)
	{
		isColliding = state;
	}

private:
	SDL_Color activeColor;
	SDL_Color defaultColor;
	bool isColliding;
};