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
//    // �V�[���Ɋ�Â��ē���̃e�N�X�`�������[�h
//    switch (sceneIndex) {
//    case SCENE_TITLE:
//        // �^�C�g���V�[���̃e�N�X�`�������[�h
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
//        delete it.second; // ���������
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
//            //���[�h�Ɏ��s����
//            //TODO:�G���[���b�Z�[�W�o��
//            delete newAnimationModel;
//        }
//    }
//    else
//    {
//        // ���ɑ��݂���L�[�̏ꍇ�A�V���� Image �I�u�W�F�N�g���쐬���Ȃ�
//        //TODO:�G���[���b�Z�[�W�o��
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
//            //���[�h�Ɏ��s����
//            //TODO:�G���[���b�Z�[�W�o��
//            delete animationModel;
//        }
//    }
//    else
//    {
//        // ���ɑ��݂���L�[�̏ꍇ�A�V���� Image �I�u�W�F�N�g���쐬���Ȃ�
//        //TODO:�G���[���b�Z�[�W�o��
//    }
//}
