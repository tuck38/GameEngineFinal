#pragma once
#include "GameObject.h"
#include "FrameAllocator.h"

namespace Tungine
{
	struct World
	{
		//INITIALIZE THIS
		static World* world;

		static SDL_Renderer* renderer;

		static int activeRendererComponents;
		static int activeColliderComponents;
		static int activeColorComponents;
		static int activeControllerComponents;

		static const int MAX_GAMEOBJECTS = 500;

		static Transform masterPoint;

		static std::vector<GameObject*> gameObjects;

		static ColliderColorChange colorChangers[MAX_GAMEOBJECTS];
		static PlayerController players[MAX_GAMEOBJECTS];
		static RectangleRenderer renderers[MAX_GAMEOBJECTS];
		static RectangleCollider colliders[MAX_GAMEOBJECTS];

		static FrameAllocator colliderStack;
		static FrameAllocator controllerStack;

		static void createColorChanger(GameObject& obj, ColliderColorChange cc);
		static void createPlayerController(GameObject& obj, PlayerController pc);
		static void createRenderer(GameObject& obj, RectangleRenderer rr);
		static void createCollider(GameObject& obj, RectangleCollider rc);

		static void Init(SDL_Renderer* rend, Transform mp);
		static void Update();
		static void Draw();

		static void objectsOverlappingPoint();

		static void Shutdown();
	};
}