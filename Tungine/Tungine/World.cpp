#include "World.h"

int Tungine::World::activeColliderComponents = 0;
int Tungine::World::activeRendererComponents = 0;
int Tungine::World::activeControllerComponents = 0;
int Tungine::World::activeColorComponents = 0;

Transform Tungine::World::masterPoint = Transform(0, 0, 0);

FrameAllocator Tungine::World::colliderStack = FrameAllocator(1024 * 1024);

FrameAllocator Tungine::World::controllerStack = FrameAllocator(1024 * 1024);

PlayerController Tungine::World::players[] = {};
RectangleRenderer Tungine::World::renderers[] = {};
RectangleCollider Tungine::World::colliders[] = {};
ColliderColorChange Tungine::World::colorChangers[] = {};

SDL_Renderer* Tungine::World::renderer =  nullptr;

LevelLoader* Tungine::World::loadLevel = nullptr;

std::vector<GameObject*> Tungine::World::gameObjects;

void Tungine::World::Init(SDL_Renderer* rend, Transform mp)
{
	masterPoint = mp;
	Tungine::World::renderer = rend;
	Tungine::World::loadLevel = new LevelLoader();
}

void Tungine::World::Draw()
{
	if (activeRendererComponents != 0)
	{
		if (activeColorComponents != 0)
		{
			for (int i = 0; i < activeColorComponents; i++)
			{
				colorChangers[i].ChangeColor();
			}
		}
		for (int i = 0; i < activeRendererComponents; i++)
		{
			renderers[i].Render(renderer);
		}
	}
}

void Tungine::World::Update()
{
	if (activeColliderComponents > 1)
	{
		for (int i = 0; i < activeColliderComponents; i++)
		{
			for (int j = 0; j < activeColliderComponents; j++)
			{
				if (&colliders[i] != &colliders[j])
				{
					colliders[i].CheckCollision(&colliders[j]);
				}
			}
		}
	}

	objectsOverlappingPoint();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}

	PlayerController** controllerArray = controllerStack.alloc<PlayerController*>(activeControllerComponents);
	int controllersWithKeypressed = 0;
	if (activeControllerComponents != 0)
	{
		for (int i = 0; i < activeControllerComponents; i++)
		{
			if (players[i].getInput())
			{
				controllerArray[controllersWithKeypressed] = &players[i];
				controllersWithKeypressed++;
			}
		}
	}

	Draw();
	colliderStack.clear();
	controllerStack.clear();
}

void::Tungine::World::objectsOverlappingPoint()
{
	RectangleCollider** colliderArray = colliderStack.alloc<RectangleCollider*>(activeColliderComponents);
	int collidersOnPoint = 0;
	if (activeColliderComponents > 1)
	{
		for (int i = 0; i < activeColliderComponents; i++)
		{
			if (colliders[i].containsPoint(masterPoint))
			{
				colliderArray[collidersOnPoint] = &colliders[i];
				collidersOnPoint++;
			}
		}
	}
}

void Tungine::World::Shutdown()
{

	for (int i = 0; i < gameObjects.size(); i++)
	{
		GameObject* obj = gameObjects[i];
		delete obj;
	}
	gameObjects.clear();

	delete loadLevel;
	delete world;
}

void Tungine::World::createColorChanger(GameObject& obj, ColliderColorChange cc)
{
	colorChangers[activeColorComponents] = cc;
	activeColorComponents++;
	obj.createColorChanger(&colorChangers[activeColorComponents - 1]);
}

void Tungine::World::createPlayerController(GameObject& obj, PlayerController pc)
{
	players[activeControllerComponents] = pc;
	activeControllerComponents++;
	obj.createController(&players[activeControllerComponents - 1]);
}

void Tungine::World::createRenderer(GameObject& obj, RectangleRenderer rr)
{
	renderers[activeRendererComponents] = rr;
	activeRendererComponents++;
	obj.createRenderer(&renderers[activeRendererComponents - 1]);
}

void Tungine::World::createCollider(GameObject& obj, RectangleCollider rc)
{
	colliders[activeColliderComponents] = rc;
	activeColliderComponents++;
	obj.createCollider(&colliders[activeColliderComponents- 1]);
}

void Tungine::World::deleteObject(GameObject* obj)
{
	int index = -1;
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] == obj)
		{
			if (gameObjects[i]->getRenderer() != nullptr)
			{
				clearRenderer(obj);
			}
			if (gameObjects[i]->getCollider() != nullptr)
			{
				clearCollider(obj);
			}
			if (gameObjects[i]->getColorChanger() != nullptr)
			{
				clearColorChanger(obj);
			}
			if (gameObjects[i]->getPlayer() != nullptr)
			{
				clearController(obj);
			}
			
			index = i;
			break;
		}
	}
	if (index >= 0)
	{
		gameObjects.erase(gameObjects.begin() + index);
	}
}

int Tungine::World::GetRendererLoc(GameObject* obj)
{
	for (int i = 0; i < activeRendererComponents; i++)
	{
		if (&renderers[i] == obj->getRenderer())
		{
			return i;
		}
	}
	return -1;
}

int Tungine::World::GetColliderLoc(GameObject* obj)
{
	for (int i = 0; i < activeColliderComponents; i++)
	{
		if (&colliders[i] == obj->getCollider())
		{
			return i;
		}
	}
	return -1;
}

int Tungine::World::GetColorChangerLoc(GameObject* obj)
{
	for (int i = 0; i < activeColorComponents; i++)
	{
		if (&colorChangers[i] == obj->getColorChanger())
		{
			return i;
		}
	}
	return -1;
}

int Tungine::World::GetControllerLoc(GameObject* obj)
{
	for (int i = 0; i < activeControllerComponents; i++)
	{
		if (&players[i] == obj->getPlayer())
		{
			return i;
		}
	}
	return -1;
}




void Tungine::World::clearRenderer(GameObject* obj)
{
	int index = -1;
	RectangleRenderer* renderer = obj->getRenderer();
	for (int i = 0; i < activeRendererComponents; i++)
	{
		if (&renderers[i] == renderer)
		{
			renderers[i] = RectangleRenderer();
			index = i;
			break;
		}
	}
	if (index >= 0)
	{
		for (int i = index; i < activeRendererComponents - 1; i++)
		{
			//Tungine::World::renderers[i] = renderers[i + 1];
		}
		//activeRendererComponents--;
	}
	
}


void Tungine::World::clearCollider(GameObject* obj)
{
	int index = -1;
	RectangleCollider* collider = obj->getCollider();
	for (int i = 0; i < activeColliderComponents; i++)
	{
		if (&colliders[i] == collider)
		{
			colliders[i] = RectangleCollider();
			index = i;
			break;
		}
	}

	if (index >= 0)
	{
		for (int i = index; i < activeColliderComponents-1; i++)
		{
			//Tungine::World::colliders[i] = colliders[i + 1];
		}

		//activeColliderComponents--;
	}

}


void Tungine::World::clearColorChanger(GameObject* obj)
{
	int index = -1;
	ColliderColorChange* colorChanger = obj->getColorChanger();
	for (int i = 0; i < activeColorComponents; i++)
	{
		if (&colorChangers[i] == colorChanger)
		{
			colorChangers[i] = ColliderColorChange();
			index = i;
			break;
		}
	}

	if (index >= 0)
	{
		for (int i = index; i < activeColorComponents-1; i++)
		{
			//Tungine::World::colorChangers[i] = colorChangers[i + 1];
		}

		//activeColorComponents--;
	}

}


void Tungine::World::clearController(GameObject* obj)
{
	int index = -1;
	PlayerController* player = obj->getPlayer();
	for (int i = 0; i < activeControllerComponents; i++)
	{
		if (&players[i] == player)
		{
			players[i] = PlayerController();
			index = i;
			break;
		}
	}

	if (index >= 0)
	{
		for (int i = index; i < activeControllerComponents-1; i++)
		{
			//Tungine::World::players[i] = players[i + 1];
		}

		//activeControllerComponents--;
	}
}


void Tungine::World::clearRenderer(int index)
{
	for (int i = index; i < activeRendererComponents; i++)
	{
		renderers[i] = renderers[i + 1];
	}
	activeRendererComponents--;
}


void Tungine::World::clearCollider(int index)
{
	for (int i = index; i < activeColliderComponents; i++)
	{
		colliders[i] = colliders[i + 1];
	}
	activeColliderComponents--;
}


void Tungine::World::clearColorChanger(int index)
{
	for (int i = index; i < activeColorComponents; i++)
	{
		colorChangers[i] = colorChangers[i + 1];
	}
	activeColorComponents--;
}


void Tungine::World::clearController(int index)
{
	for (int i = index; i < activeControllerComponents; i++)
	{
		players[i] = players[i + 1];
	}
	activeControllerComponents--;
}

RectangleCollider* Tungine::World::FindObjectAtPoint(Transform t)
{
	RectangleCollider* r = nullptr;
	for (int i = 0; i < activeColliderComponents; i++)
	{
		if (colliders[i].containsPoint(t))
		{
			return &colliders[i];
		}
	}

	return r;
}