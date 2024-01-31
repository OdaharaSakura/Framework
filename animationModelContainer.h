//#pragma once
//
//#include "animationModel.h"
//
//
//#include <unordered_map>
//#include <string>
//
//class AnimationModelContainer
//{
//private:
//	static std::unordered_map<std::string, AnimationModel*> m_AnimationModelDictionary;//�L�[ + Image
//	static std::unordered_map<std::string, const aiScene*> m_AnimationDictionary;
//
//	static std::string m_FBXAnimationsFrontPath;//�t�@�C���̃p�X
//
//public:
//	enum SceneType
//	{
//		Scene_Title,
//		Scene_Game,
//		Scene_Result,
//		Scene_Max
//	};
//
//	//scene�ɂ���Ăǂ��ǂݍ��ނ������߂�
//	static void Load(int sceneIndex);
//	static void Unload(int sceneIndex);
//
//
//	static AnimationModel* GetAnimationModel_Key(std::string key);
//	static aiScene* GetAnimation_Key(std::string key);
//
//	static void AddAnimationModel(std::string key, std::string path);
//	static void AddAnimation(std::string animationModelKey, std::string key, std::string path);
//};