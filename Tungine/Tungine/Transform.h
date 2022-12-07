#pragma once

class Transform
{
public:

	Transform()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Transform(int X, int Y, int Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	int getZ()
	{
		return z;
	}

	void move(int moveX, int moveY, int moveZ);

private:
	int x, y, z;
};