#pragma once
#include "image.h"
#include <unordered_map>
#include <string>



class TextureContainer
{
private:
	static std::unordered_map<std::string, Image*> m_ImageDictionary;//キー + Image
	static std::string m_FrontPath;//ファイルのパス

public:

	//sceneによってどれを読み込むかを決める
	static void Load(int sceneIndex);
	static void Unload(int sceneIndex);


	static Image* GetImage_Path(std::string path);
	static Image* GetImage_Key(std::string key);

	static void AddImage(std::string key, std::string path);
};