#pragma once
#include <SDL.h>
#include "Transform.h"

class RectangleRenderer
{
public:

	RectangleRenderer()
	{
		height = 0;
		width = 0;
		defaultColor = SDL_Color();
		color = SDL_Color();
		transform = Transform();
		rect = SDL_Rect();
	}

	RectangleRenderer(float h, float w, SDL_Color c, Transform t)
	{
		height = h;
		width = w;
		defaultColor = c;
		color = c;
		transform = t;
		rect = SDL_Rect({transform.getX(), transform.getY(), (int)height, (int)width});
	}

	void Render(SDL_Renderer* renderer);

	float getHeight()
	{
		return height;
	}

	float getWidth()
	{
		return width;
	}

	SDL_Color getColor()
	{
		return color;
	}

	SDL_Color getDefaultColor()
	{
		return defaultColor;
	}

	void setTransform(Transform t)
	{
		transform = t;
	}

	Transform getTransform()
	{
		return transform;
	}

	void setColor(SDL_Color newColor)
	{
		color = newColor;
	}

private:
	float height, width;
	SDL_Rect rect;
	SDL_Color color;
	SDL_Color defaultColor;
	Transform transform;
};