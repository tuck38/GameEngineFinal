#pragma once
#include "Transform.h"
#include <SDL.h>

class PlayerController
{
public:

	PlayerController()
	{
		transform = Transform();
		moveValue = 0;
	}

	PlayerController(float val, Transform t)
	{
		transform = t;
		moveValue = val;
	}

	bool getInput();

	Transform& getTransform()
	{
		return transform;
	}

private:
	Transform transform;
	float moveValue;
};