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

std::vector<GameObject*> Tungine::World::gameObjects;

void Tungine::World::Init(SDL_Renderer* rend, Transform mp)
{
	masterPoint = mp;
	Tungine::World::renderer = rend;
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
