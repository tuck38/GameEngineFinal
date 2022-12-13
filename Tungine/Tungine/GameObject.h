#pragma once
#include "RectangleCollider.h"
#include "PlayerController.h"
#include "ColliderColorChanger.h"
#include "System_Common.h"
#include <vector>

class GameObject
{
public:
	GameObject()
	{

	}

	GameObject(Transform t, float h, float w)
	{
		height = h;
		width = w;

		isColliding = false;

		transform = t;
		renderer = nullptr;
		collider = nullptr;
		controller = nullptr;
		colorChanger = nullptr;
	}

	~GameObject()
	{
		/*
		if (renderer != nullptr) delete renderer;
		if (collider != nullptr) delete collider;
		if (controller != nullptr) delete controller;
		if (colorChanger != nullptr) delete colorChanger;
		*/
	}

	float getHeight()
	{
		return height;
	}

	float getWidth()
	{
		return width;
	}

	void setWidth(int newWidth) { width = newWidth; }
	void setHeight(int newHeight) { height = newHeight; }

	void setTransform(Transform t)
	{
		transform = t;
	}

	void setHW(float h, float w)
	{
		height = h;
		width = w;
	}

	Transform& getTransform()
	{
		return transform;
	}

	RectangleRenderer* getRenderer()
	{
		return renderer;
	}
	PlayerController* getPlayer()
	{
		return controller;
	}
	RectangleCollider* getCollider()
	{
		return collider;
	}
	ColliderColorChange* getColorChanger()
	{
		return colorChanger;
	}

	/*RectangleRenderer* createRenderer(SDL_Color c);
	ColliderColorChange* createColorChanger();
	RectangleCollider* createCollider(Transform t);
	PlayerController* createController(float val);*/

	RectangleRenderer* createRenderer(RectangleRenderer *r);
	ColliderColorChange* createColorChanger(ColliderColorChange *c);
	RectangleCollider* createCollider(RectangleCollider *c);
	PlayerController* createController(PlayerController *c);

	void Update();

	Tungine::string PrintObject(int id);

	void changeWidth(int diff);
	void changeHeight(int diff);

	void setName(std::string value) { name = value; }
	std::string getName() { return name; }
protected:
	float height;
	float width;

	bool isColliding;

	std::string name;

	Transform transform;
	RectangleRenderer* renderer;
	RectangleCollider* collider;
	PlayerController* controller;
	ColliderColorChange* colorChanger;
};