//#include "main.h"
//#include "renderer.h"
//#include "animationModelContainer.h"
//#include "scene.h"
//#include <algorithm>
//
//
//std::unordered_map<std::string, AnimationModel*> AnimationModelContainer::m_AnimationModelDictionary{};
//std::unordered_map<std::string, AnimationModel*> AnimationModelContainer::m_AnimationDictionary{};
//
//std::string AnimationModelContainer::m_FBXAnimationsFrontPath = "asset\\model\\fbx\\";
//
//void AnimationModelContainer::Load(int sceneIndex)
//{
//
//
//    // シーンに基づいて特定のテクスチャをロード
//    switch (sceneIndex) {
//    case SCENE_TITLE:
//        // タイトルシーンのテクスチャをロード
//        //AddImage("titleBackground", "path/to/title_background.png");
//        break;
//    case SCENE_GAME:
//    {
//        LoadAnimationModelData("Player", "Player.fbx");
//        LoadAnimationData("Player", "Idle", "Player_Idle.fbx");
//        LoadAnimationData("Player", "Run", "Player_Run.fbx");
//        LoadAnimationData("Player", "LeftRun", "Player_LeftRun.fbx");
//        LoadAnimationData("Player", "RightRun", "Player_RightRun.fbx");
//        LoadAnimationData("Player", "BackRun", "Player_BackRun.fbx");
//        LoadAnimationData("Player", "Attack", "Player_Attack.fbx");
//        LoadAnimationData("Player", "Death", "Player_Death.fbx");
//        LoadAnimationData("Player", "InPlaceJump", "Player_InPlaceJump.fbx");
//    }
//    break;
//    case SCENE_RESULT:
//        break;
//    default:
//        break;
//    }
//}
//
//void AnimationModelContainer::Unload(int sceneIndex)
//{
//    for (auto& it : m_AnimationModelDictionary) {
//        delete it.second; // メモリ解放
//        it.second = nullptr;
//    }
//    m_AnimationModelDictionary.clear();
//}
//
//
//
//
//AnimationModel* AnimationModelContainer::GetAnimationModel_Key(std::string key)
//{
//    auto it = m_AnimationModelDictionary.find(key);
//    if (it != m_AnimationModelDictionary.end()) {
//        return it->second;
//    }
//    else {
//        return nullptr;
//    }
//}
//
//
//AnimationModel* AnimationModelContainer::GetAnimation_Key(std::string key)
//{
//    auto it = m_AnimationDictionary.find(key);
//    if (it != m_AnimationDictionary.end()) {
//        return it->second;
//    }
//    else {
//        return nullptr;
//    }
//}
//
//
//
//void AnimationModelContainer::LoadAnimationModelData(std::string key, std::string path)
//{
//
//    std::string fullPath = m_FBXAnimationsFrontPath + path;
//
//    auto it = m_AnimationModelDictionary.find(key);
//    if (it == m_AnimationModelDictionary.end()) {
//        AnimationModel* newAnimationModel = new AnimationModel;
//        newAnimationModel->Load(fullPath.c_str());
//
//        if (newAnimationModel != nullptr)
//        {
//            m_AnimationModelDictionary[key] = newAnimationModel;
//        }
//        else
//        {
//            //ロードに失敗した
//            //TODO:エラーメッセージ出す
//            delete newAnimationModel;
//        }
//    }
//    else
//    {
//        // 既に存在するキーの場合、新しい Image オブジェクトを作成しない
//        //TODO:エラーメッセージ出す
//    }
//}
//
//void AnimationModelContainer::LoadAnimationData(std::string animationModelKey, std::string key, std::string path)
//{
//
//    std::string fullPath = m_FBXAnimationsFrontPath + path;
//
//    auto it = m_AnimationDictionary.find(animationModelKey + key);
//    if (it == m_AnimationDictionary.end()) {
//        AnimationModel* animationModel = GetAnimationModel_Key(animationModelKey);
//
//        animationModel->LoadAnimation(fullPath.c_str(), key.c_str());
//
//        if (animationModel != nullptr)
//        {
//            m_AnimationModelDictionary[animationModelKey] = animationModel;
//            m_AnimationDictionary[animationModelKey + key] = animationModel;
//        }
//        else
//        {
//            //ロードに失敗した
//            //TODO:エラーメッセージ出す
//            delete animationModel;
//        }
//    }
//    else
//    {
//        // 既に存在するキーの場合、新しい Image オブジェクトを作成しない
//        //TODO:エラーメッセージ出す
//    }
//}
