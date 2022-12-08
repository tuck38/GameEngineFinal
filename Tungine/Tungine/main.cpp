#include "system.h"
#include "GameObject.h"
#include "World.h"
#include "FrameAllocator.h"

struct EngineState
{
    SDL_Renderer* renderer;
    Tungine::System* system;
    Uint32 frameStart;
    bool quit;
    int frame;

    GameObject* placement;
    int placeX;
    int placeY;
};

Tungine::World* Tungine::World::world = nullptr;

void runMainLoop(EngineState* engine);
void frameStep(void* arg);
Uint32 GetTicks();

int main(int argc, char* argv[])
{
    const int WIDTH = 640;
    const int HEIGHT = 480;
    const int moveSpeed = 5;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    Tungine::System* system = Tungine::System::Create();
    system->Init();

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Transform mp = Transform(WIDTH / 2, HEIGHT / 2, 1);

    Tungine::World::Init(renderer, mp);

    EngineState engine;
    engine.quit = false;
    engine.renderer = renderer;
    engine.frame = 0;
    engine.frameStart = GetTicks();
    engine.system = system;
    engine.placement = nullptr;

    GameObject* backdrop = new GameObject(Transform(0, 0, 0), WIDTH, HEIGHT);

    Tungine::World::createRenderer(*backdrop, RectangleRenderer(backdrop->getHeight(), backdrop->getWidth(), SDL_Color{ 0, 0, 0 }, backdrop->getTransform()));

    Tungine::World::gameObjects.push_back(backdrop);

    GameObject* player = new GameObject(Transform(10, HEIGHT / 2, 1), 50, 50);

    Tungine::World::createRenderer(*player, RectangleRenderer(player->getHeight(), player->getWidth(), SDL_Color{255, 1, 1}, player->getTransform()));
    Tungine::World::createColorChanger(*player, ColliderColorChange(SDL_Color{255, 1, 1}));
    Tungine::World::createCollider(*player, RectangleCollider(player->getHeight(), player->getWidth(), player->getTransform()));
    Tungine::World::createPlayerController(*player, PlayerController(moveSpeed, player->getTransform()));

   Tungine::World::gameObjects.push_back(player);

    GameObject* collidable = new GameObject(Transform(WIDTH - 100, HEIGHT / 2, 1), 50, 50);

    Tungine::World::createRenderer(*collidable, RectangleRenderer(collidable->getHeight(), collidable->getWidth(), SDL_Color{1, 255, 1}, collidable->getTransform()));
    Tungine::World::createColorChanger(*collidable, ColliderColorChange(SDL_Color{1, 255, 1}));
    Tungine::World::createCollider(*collidable, RectangleCollider(collidable->getHeight(), collidable->getWidth(), collidable->getTransform()));

    Tungine::World::gameObjects.push_back(collidable);

    GameObject* collidable2 = new GameObject(Transform(WIDTH - 300, HEIGHT / 4, 1), 50, 50);

    Tungine::World::createRenderer(*collidable2, RectangleRenderer(collidable2->getHeight(), collidable2->getWidth(), SDL_Color{ 1, 255, 255 }, collidable2->getTransform()));
    Tungine::World::createColorChanger(*collidable2, ColliderColorChange(SDL_Color{ 1, 255, 255 }));
    Tungine::World::createCollider(*collidable2, RectangleCollider(collidable2->getHeight(), collidable2->getWidth(), collidable2->getTransform()));

    Tungine::World::gameObjects.push_back(collidable2);

    //LEGACY COMPONENT CREATION
    /*GameObject* player = new GameObject(Transform(10, HEIGHT / 2, 1), 50, 50);

    player->createRenderer(SDL_Color{ 255, 1, 1 });
    player->createColorChanger();
    engine.colliders.push_back(player->createCollider(Transform(10, HEIGHT / 2, 1)));
    player->createController(moveSpeed);

   engine.gameObjects.push_back(player);

    GameObject* collidable = new GameObject(Transform(WIDTH - 100, HEIGHT / 2, 1), 50, 50);

    collidable->createRenderer(SDL_Color{ 1, 255, 1 });
    collidable->createColorChanger();
    engine.colliders.push_back(collidable->createCollider(Transform(WIDTH - 100, HEIGHT / 2, 1)));

    engine.gameObjects.push_back(collidable);

    GameObject* backdrop = new GameObject(Transform(0, 0, 0), HEIGHT, WIDTH);

    backdrop->createRenderer(SDL_Color{ 255, 255, 255 });

    engine.gameObjects.push_back(backdrop);*/

    runMainLoop(&engine);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    Tungine::World::Shutdown();

    system->Shutdown();
    
    delete system;
    return 0;
}

void runMainLoop(EngineState* engine)
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(&frameStep, engine, 0, true);
#elif _WIN32
    while (!engine->quit)
    {
        Uint32 now = GetTicks();
        if (now - engine->frameStart >= 16)
        {
            frameStep(engine);
        }
    }
#endif 
}

void frameStep(void* arg)
{
    EngineState* engine = (EngineState*)arg;
    SDL_Event event;

    Uint32 now = GetTicks();

    engine->frame++;
    engine->frameStart = now;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            engine->quit = true;
        }

        if (event.type == SDL_KEYDOWN)
        {

           // std::cout << "Key pressed!\n";
            if (event.key.keysym.sym == SDLK_k)
            {
                std::cout << "K pressed!\n";

                engine->system->ShowError(Tungine::error);
            }

            if (Tungine::World::MAX_GAMEOBJECTS < Tungine::World::gameObjects.size())
            {
                engine->system->ShowError(Tungine::errorGameObject);
                engine->quit = true;
            }

            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                engine->quit = true;
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT && engine->placement == nullptr)
            {
                engine->placeX = event.button.x;
                engine->placeY = event.button.y;
                engine->placement = new GameObject(Transform(event.button.x, event.button.y, 0), 0, 0); //width and height will be changed as the mouse moves
                Tungine::World::createRenderer(*engine->placement, RectangleRenderer(engine->placement->getHeight(), engine->placement->getWidth(), SDL_Color{ 1, 255, 1 }, engine->placement->getTransform()));
                Tungine::World::createCollider(*engine->placement, RectangleCollider(engine->placement->getHeight(), engine->placement->getWidth(), engine->placement->getTransform()));
                Tungine::World::gameObjects.push_back(engine->placement);
            }
        }
        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
        {
            if (engine->placement != nullptr)
            {
                GameObject* newObject = new GameObject(Transform(engine->placement->getTransform().getX(), engine->placement->getTransform().getY(), 1), 
                    engine->placement->getRenderer()->getHeight(), engine->placement->getRenderer()->getWidth());

                Tungine::World::createRenderer(*newObject, RectangleRenderer(newObject->getHeight(), newObject->getWidth(), SDL_Color{ 1, 255, 255 }, newObject->getTransform()));
                Tungine::World::createColorChanger(*newObject, ColliderColorChange(SDL_Color{ 1, 255, 255 }));
                Tungine::World::createCollider(*newObject, RectangleCollider(newObject->getWidth(), newObject->getHeight(), newObject->getTransform()));

                Tungine::World::gameObjects.push_back(newObject);


                Tungine::World::deleteObject(*engine->placement);
                delete engine->placement;
                engine->placement = nullptr;
            }
            
        }

    }

    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderClear(engine->renderer);

    if (engine->placement != nullptr)
    {
        int *x = new int;
        int *y = new int;
        SDL_GetMouseState(x, y);
        engine->placement->getRenderer()->setWidth(*y - engine->placeY);
        engine->placement->getRenderer()->setHeight(*x - engine->placeX);
        delete x;
        delete y;
    }


    Tungine::World::Update();

    SDL_SetRenderDrawColor(engine->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(engine->renderer);
}

Uint32 GetTicks()
{
    return SDL_GetTicks();
}