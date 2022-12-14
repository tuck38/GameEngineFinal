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

	if (renderer != nullptr)
	{
		renderer->setTransform(transform);
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

std::string GameObject::PrintObject(int id)//pass the object's place in World::gameobjects
{
	//object id | transform | HW |  Renderer || colorchanger | collider | player controller
	//ex: 1| 0 [400.0 250.0 0]| 1 [50 50]| 2 [100.0 20.5 40.7]| 3 [100.0 20.5 40.7]| 4 [0.0]| 5 [5.0]|
	// 0 - transform [x y z] 1 - renderer [width height r g b] 2 - collider

	//Tungine::string result;

	std::stringstream f;

	f << id << "| ";
	//result.append(id + L", ");

	//transform
	//result.append(L"0 [" + transform.getX() + L" " + transform.getY() + L" " + transform.getZ() + L"], ");
	f << "0 [" << (int)transform.getX() << " " << (int)transform.getY() << " 0" << "]|";

	//height and width
	f << " 1 [" << height << " " << width << "]|";

	//renderer
	if (renderer != nullptr) f << " 2 [" << (float)renderer->getColor().r << " " << (float)renderer->getColor().g << " " << (float)renderer->getColor().b << "]|";

	//collider
	if (colorChanger != nullptr) f << " 3 [" << (float)renderer->getColor().r << " " << (float)renderer->getColor().g << " " << (float)renderer->getColor().b << "]|";

	//player controller
	if (collider != nullptr) f << " 4 [0.0]|";

	//color changer
	if (controller != nullptr) f << " 5 [0.0]|";

	f << std::endl;



	std::string result = f.str();
	return result;

	//result = Tungine::ConvertStream(f);
	//return result;
	//return L"";
}

void GameObject::changeHeight(int diff)
{
	height += diff;
	if (height < 10) height = 10;
	if (collider != nullptr) collider->setHeight(height);
	if (renderer != nullptr) renderer->setHeight(height);
}
void GameObject::changeWidth(int diff)
{
	width += diff;
	if (width < 10) width = 10;
	if (collider != nullptr) collider->setWidth(width);
	if (renderer != nullptr) renderer->setWidth(width);
}
