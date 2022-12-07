#pragma once
#include "ColliderColorChanger.h"

class RectangleCollider
{
public:

	RectangleCollider()
	{
		height = 0;
		width = 0;
		transform = Transform();

		isColliding = false;

		topLeft = Transform();
		bottomRight = Transform();
		topRight = Transform();
		bottomLeft = Transform();
	}

	RectangleCollider(float h, float w, Transform t)
	{
		height = h;
		width = w;
		transform = t;

		isColliding = false;

		topLeft = t;
		bottomRight = Transform(t.getX() - width, t.getY() - height, 0);
		topRight = Transform(t.getX() - width, t.getY(), 0);
		bottomLeft = Transform(t.getX(), t.getY() - height, 0);
	}

	void CheckCollision(RectangleCollider* other);

	bool containsPoint(Transform t);             

	float getHeight()
	{
		return height;
	}

	float getWidth()
	{
		return width;
	}

	bool& getState()
	{
		return isColliding;
	}

	void setTransform(Transform t)
	{
		transform = t;
		topLeft = t;
		bottomRight = Transform(t.getX() - width, t.getY() - height, 0);
		topRight = Transform(t.getX() - width, t.getY(), 0);
		bottomLeft = Transform(t.getX(), t.getY() - height, 0);
	}

	Transform getTransform()
	{
		return transform;
	}

private:
	float height, width;

	bool isColliding;

	//edge points
	Transform topLeft, topRight, bottomLeft, bottomRight;

	Transform transform;
};
