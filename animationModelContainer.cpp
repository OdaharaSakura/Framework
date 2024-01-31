//#include "animationModelContainer.h"
//#include <algorithm>
//
//
//std::unordered_map<std::string, AnimationModel*> AnimationModelContainer::m_AnimationModelDictionary{};
//std::unordered_map<std::string, const aiScene*> AnimationModelContainer::m_AnimationDictionary{};
//
//std::string AnimationModelContainer::m_FBXAnimationsFrontPath = "asset/model/fbx/";
//
//void AnimationModelContainer::Load(int sceneIndex)
//{
//
//
//    // �V�[���Ɋ�Â��ē���̃e�N�X�`�������[�h
//    switch (sceneIndex) {
//    case Scene_Title:
//        // �^�C�g���V�[���̃e�N�X�`�������[�h
//        //AddImage("titleBackground", "path/to/title_background.png");
//        break;
//    case Scene_Game:
//    {
//
//    }
//    break;
//    case Scene_Result:
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
//const aiScene* AnimationModelContainer::GetAnimation_Key(std::string key)
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
//void AnimationModelContainer::AddAnimationModel(std::string key, std::string path)
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
//void AnimationModelContainer::AddAnimation(std::string animationModelKey, std::string key, std::string path)
//{
//
//    std::string fullPath = m_FBXAnimationsFrontPath + path;
//
//    auto it = m_AnimationDictionary.find(animationModelKey + key);
//    if (it == m_AnimationDictionary.end()) {
//        AnimationModel* newAnimationModel = GetAnimationModel_Key(animationModelKey);
//
//        newAnimationModel->LoadAnimation(fullPath.c_str(), key.c_str());
//
//        if (newAnimationModel != nullptr)
//        {
//            m_AnimationModelDictionary[animationModelKey + key] = newAnimationModel;
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
