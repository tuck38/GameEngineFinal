#include "Transform.h"

void Transform::move(int moveX, int moveY, int moveZ)
{
	x += moveX;
	y += moveY;
	z += moveZ;
}