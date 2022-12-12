#include "GameObject.h"
#include <string>
#include <sstream>
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
	collider->setObject(this);
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

Tungine::string GameObject::PrintObject(int id)//pass the object's place in World::gameobjects
{
	//[Obj ID], [compID] [parameters], [compID], [compID],
	//ex: 1, 0 [20.0 40.0 0.0], 1 [40.0 60.0 255 255 255], 2,
	// 0 - transform [x y z] 1 - renderer [width height r g b] 2 - collider

	Tungine::string result;

	std::stringstream f;

	f << id << ", ";
	//result.append(id + L", ");

	//transform
	//result.append(L"0 [" + transform.getX() + L" " + transform.getY() + L" " + transform.getZ() + L"], ");
	f << "0 [" << transform.getX() << " " << transform.getY() << " " + transform.getZ() << "], ";


	//renderer
	if (renderer != nullptr) f << "1 [" << renderer->getWidth() << " " << renderer->getHeight() << " " << renderer->getColor().r << " " + 
		renderer->getColor().g << " " << renderer->getColor().b << "], ";

	//collider
	if (collider != nullptr) f << "2, ";

	//player controller
	if (controller != nullptr) f << "3, ";

	//color changer
	if (colorChanger != nullptr) f << "4, ";

	f << std::endl;

	//result = Tungine::ConvertStream(f);
	//return result;
	return L"";
}

void GameObject::changeHeight(int diff)
{
	height += diff;
	if (collider != nullptr) collider->setHeight(height);
	if (renderer != nullptr) renderer->setHeight(height);
}
void GameObject::changeWidth(int diff)
{
	width += diff;
	if (collider != nullptr) collider->setWidth(width);
	if (renderer != nullptr) renderer->setWidth(width);
}
