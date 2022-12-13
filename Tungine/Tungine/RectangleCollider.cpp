#include "RectangleCollider.h"

void RectangleCollider::CheckCollision(RectangleCollider* other)
{
	/*
	if (topLeft.getX() <= other->topLeft.getX() && topLeft.getX() >= other->bottomRight.getX() && topLeft.getY() <= other->topLeft.getY() && topLeft.getY() >= other->bottomRight.getY() ||
		topRight.getX() <= other->topLeft.getX() && topRight.getX() >= other->bottomRight.getX() && topRight.getY() <= other->topLeft.getY() && topRight.getY() >= other->bottomRight.getY() || 
		bottomLeft.getX() <= other->topLeft.getX() && bottomLeft.getX() >= other->bottomRight.getX() && bottomLeft.getY() <= other->topLeft.getY() && bottomLeft.getY() >= other->bottomRight.getY() || 
		bottomRight.getX() <= other->topLeft.getX() && bottomRight.getX() >= other->bottomRight.getX() && bottomRight.getY() <= other->topLeft.getY() && bottomRight.getY() >= other->bottomRight.getY())
	{
		isColliding = true;
	}
	else
	{
		isColliding = false;
	}
	*/
	//leaving it here to shame you
	if (topLeft.getX() > other->bottomRight.getX() || bottomRight.getX() < other->topLeft.getX()) //rectangles separate on the x axis
	{
		isColliding = false;
		return;
	}

	if (topLeft.getY() > other->bottomRight.getY() || bottomRight.getY() < other->topLeft.getY()) //rectangles separate on the y axis
	{
		isColliding = false;
		return;
	}

	isColliding = true;


}

bool RectangleCollider::containsPoint(Transform t)
{
	//if (topLeft.getX() <= t.getX() && topLeft.getY() >= t.getY() && bottomRight.getX() >= t.getX() && bottomRight.getY() <= t.getY())
	if(t.getX() >= topLeft.getX() && t.getX() <= bottomRight.getX() && t.getY() >= topLeft.getY() && t.getY() <= bottomRight.getY())
	{
		return true;
	}

	return false;
}


void RectangleCollider::setHeight(int value)
{
	height = value;
	bottomRight = Transform(transform.getX() - width, transform.getY() + height, 0);
	bottomLeft = Transform(transform.getX(), transform.getY() + height, 0);
}

void RectangleCollider::setWidth(int value)
{
	width = value;
	bottomRight = Transform(transform.getX() - width, transform.getY() + height, 0);
	topRight = Transform(transform.getX() - width, transform.getY(), 0);
}

/*

transform = t;
		topLeft = t;
		bottomRight = Transform(t.getX() - width, t.getY() + height, 0);
		topRight = Transform(t.getX() - width, t.getY(), 0);
		bottomLeft = Transform(t.getX(), t.getY() + height, 0);
*/