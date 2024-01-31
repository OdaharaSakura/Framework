#pragma once

#include "model.h"

#include <unordered_map>
#include <string>

class ModelContainer
{
private:
	static std::unordered_map<std::string, Model*> m_ModelDictionary;//キー + Image


	static std::string m_ModelsFrontPath;//ファイルのパス


public:

	//sceneによってどれを読み込むかを決める
	static void Load(int sceneIndex);
	static void Unload(int sceneIndex);

	static Model* GetModel_Key(std::string key);

	static void AddModel(std::string key, std::string path);

};