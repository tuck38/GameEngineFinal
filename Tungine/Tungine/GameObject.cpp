#include "GameObject.h"

void GameObject::Update()
{
	if (controller != nullptr)
	{
		transform = controller->getTransform();
		renderer->setTransform(transform);
		if (collider != nullptr)
		{
			collider->setTransform(transform);
		}
	}

	if (collider != nullptr)
	{
		isColliding = collider->getState();
		if (colorChanger != nullptr)
		{
			colorChanger->setState(isColliding);
			renderer->setColor(colorChanger->getActiveColor());
		}
	}
}

RectangleRenderer* GameObject::createRenderer(RectangleRenderer *r)
{
	renderer = r;
	return renderer;
}

ColliderColorChange* GameObject::createColorChanger(ColliderColorChange *c)
{
	colorChanger = c;
	return colorChanger;
}

RectangleCollider* GameObject::createCollider(RectangleCollider *c)
{
	collider = c;
	return collider;
}

PlayerController* GameObject::createController(PlayerController *c)
{
	controller = c;
	return controller;
}


//Legacy components
/*RectangleRenderer* GameObject::createRenderer(SDL_Color c)
{
	return renderer = new RectangleRenderer(height, width, c, transform);
}

RectangleCollider* GameObject::createCollider(Transform t)
{
	return collider = new RectangleCollider(height, width, t);
}

PlayerController* GameObject::createController(float val)
{
	return controller = new PlayerController(val);
}

ColliderColorChange* GameObject::createColorChanger()
{
	return colorChanger = new ColliderColorChange(renderer->getDefaultColor());
}*/
