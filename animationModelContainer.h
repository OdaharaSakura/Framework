//#pragma once
//
//#include "animationModel.h"
//#include <unordered_map>
//#include <string>
//
//class AnimationModelContainer
//{
//private:
//	static std::unordered_map<std::string, AnimationModel*> m_AnimationModelDictionary;//キー + Image
//	static std::unordered_map<std::string, AnimationModel*> m_AnimationDictionary;
//
//	static std::string m_FBXAnimationsFrontPath;//ファイルのパス
//
//public:
//
//	//sceneによってどれを読み込むかを決める
//	static void Load(int sceneIndex);
//	static void Unload(int sceneIndex);
//
//
//	static AnimationModel* GetAnimationModel_Key(std::string key);
//	static AnimationModel* GetAnimation_Key(std::string key);
//
//	static void LoadAnimationModelData(std::string key, std::string path);
//	static void LoadAnimationData(std::string animationModelKey, std::string key, std::string path);
//};