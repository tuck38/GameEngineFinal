#pragma once
#include "GameObject.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>


class LevelLoader
{
public:

	LevelLoader()
	{

	}

	void loadLevel(std::string filename);

	void createTransformWithFile(GameObject& obj, std::vector<float> info);
	void createHWWithFile(GameObject& obj, std::vector<float> info);
	void createColorChangerWithFile(GameObject& obj, std::vector<float> info);
	void createPlayerControllerWithFile(GameObject& obj, std::vector<float> info);
	void createRendererWithFile(GameObject& obj, std::vector<float> info);
	void createColliderWithFile(GameObject& obj, std::vector<float> info);

	void WriteLevelToFile();
};