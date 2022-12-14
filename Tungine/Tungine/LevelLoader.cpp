#include "LevelLoader.h"
#include "World.h"

//Loads in the level based on sereialized information
void LevelLoader::loadLevel(std::string filename)
{
	std::ifstream fin;

	fin.open(filename);

	typedef void (LevelLoader::* FunctionPointer)(GameObject& obj, std::vector<float> info);
	static FunctionPointer funcPtrs[] = { &LevelLoader::createTransformWithFile, &LevelLoader::createHWWithFile, &LevelLoader::createRendererWithFile,
		&LevelLoader::createColorChangerWithFile, &LevelLoader::createColliderWithFile, &LevelLoader::createPlayerControllerWithFile };

	if (fin)
	{
		while (!fin.eof())
		{
			int id;

			std::string line;

			getline(fin, line);

			std::stringstream ss(line);

			std::string objNum;

			std::string component;

			getline(ss, objNum, '|');

			std::cout << "obj id: " << objNum << " ";

			GameObject* obj = new GameObject();

			while (ss)
			{

				getline(ss, component, '|');

				if (!component.empty())
				{

					std::stringstream compInfo(component);

					int componentID;

					compInfo >> componentID;

					std::cout << "component id: " << componentID << " data: ";

					std::string info;

					getline(compInfo, info);
					int begining = info.find('[') + 1;

					int end = info.find(']');

					info = info.substr(begining, end - begining);

					std::stringstream compData(info);

					std::vector<float> nums;

					while (!compData.eof())
					{
						float num;

						compData >> num;

						nums.push_back(num);

						std::cout << num << " ";
					}

					//call list here
					(this->*funcPtrs[componentID])(*obj, nums);
				}

			}
			Tungine::World::gameObjects.push_back(obj);
			std::cout << std::endl;
		}
	}
}

//All functions assume the user is nice and only passes in requiered variables
void LevelLoader::createTransformWithFile(GameObject& obj, std::vector<float> info)
{
	Transform t = Transform(info[0], info[1], info[2]);
	obj.setTransform(t);
}

void LevelLoader::createHWWithFile(GameObject& obj, std::vector<float> info)
{
	obj.setHW(info[0], info[1]);
}

void LevelLoader::createColorChangerWithFile(GameObject& obj, std::vector<float> info)
{
	SDL_Color color = { info[0], info[1], info[2] };
	ColliderColorChange c = ColliderColorChange(color);
	Tungine::World::createColorChanger(obj, c);
}

void LevelLoader::createPlayerControllerWithFile(GameObject& obj, std::vector<float> info)
{
	PlayerController pc = PlayerController(info[0], obj.getTransform());
	Tungine::World::createPlayerController(obj, pc);
}

void LevelLoader::createRendererWithFile(GameObject& obj, std::vector<float> info)
{
	SDL_Color color = { info[0], info[1], info[2] };
	RectangleRenderer rr = RectangleRenderer(obj.getHeight(), obj.getWidth(), color, obj.getTransform());
	Tungine::World::createRenderer(obj, rr);
}

void LevelLoader::createColliderWithFile(GameObject& obj, std::vector<float> info)
{
	RectangleCollider rc = RectangleCollider(obj.getHeight(), obj.getWidth(), obj.getTransform());

	Tungine::World::createCollider(obj, rc);
}


void LevelLoader::WriteLevelToFile()
{
	HANDLE fileToWrite;
	fileToWrite = CreateFileW(L"Level1.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//WriteFile(file, message.c_str(), message.size() * sizeof(wchar_t), 0, NULL);
	std::stringstream ss;
	for (int i = 0; i < Tungine::World::gameObjects.size(); i++)
	{
		ss << Tungine::World::gameObjects[i]->PrintObject(i);
	}
	std::string result = ss.str();
	WriteFile(fileToWrite, result.c_str(), result.size() * sizeof(wchar_t), 0, NULL);
}

