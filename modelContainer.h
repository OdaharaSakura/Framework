#pragma once

#include "model.h"

#include <unordered_map>
#include <string>

class ModelContainer
{
private:
	static std::unordered_map<std::string, Model*> m_ModelDictionary;//�L�[ + Image


	static std::string m_ModelsFrontPath;//�t�@�C���̃p�X


public:

	//scene�ɂ���Ăǂ��ǂݍ��ނ������߂�
	static void Load(int sceneIndex);
	static void Unload(int sceneIndex);

	static Model* GetModelKey(std::string key);
	static Model* GetModelPath(std::string path);

	static void LoadModelData(std::string key, std::string path);

};