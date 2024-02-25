#include "main.h"
#include "renderer.h"
#include "animationModelContainer.h"
#include "scene.h"
#include <algorithm>


std::unordered_map<int, AnimationModel*> AnimationModelContainer::m_AnimationModelDictionary{};

AnimationModel* AnimationModelContainer::m_FBXModel[FBXModel::FBXModel_Max] = { new AnimationModel()};

std::string AnimationModelContainer::m_FBXAnimationsFrontPath = "asset\\model\\fbx\\";

void AnimationModelContainer::Load(int sceneIndex)
{
    for (int i = 0; i < FBXModel::FBXModel_Max; i++) {
        if (!m_FBXModel[i])
        {
            m_FBXModel[i] = new AnimationModel();
        }
    }

    // シーンに基づいて特定のテクスチャをロード
    switch (sceneIndex) {
    case SCENE_TITLE:
        m_FBXModel[FBXModel::FBXModel_ResultPlayer]->Load("asset\\model\\fbx\\Player.fbx");
        m_FBXModel[FBXModel::FBXModel_ResultPlayer]->LoadAnimation("asset\\model\\fbx\\Player_Idle.fbx", PlayerAnimation::Player_Idle);
        m_FBXModel[FBXModel::FBXModel_ResultPlayer]->LoadAnimation("asset\\model\\fbx\\Player_Run.fbx", PlayerAnimation::Player_Run);
        LoadAnimationModelData(FBXModel::FBXModel_ResultPlayer, m_FBXModel[FBXModel::FBXModel_ResultPlayer]);
        break;
    case SCENE_GAME:
    {
        m_FBXModel[FBXModel::FBXModel_Player]->Load("asset\\model\\fbx\\Player.fbx");
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("asset\\model\\fbx\\Player_Idle.fbx", PlayerAnimation::Player_Idle);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("asset\\model\\fbx\\Player_Run.fbx", PlayerAnimation::Player_Run);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("asset\\model\\fbx\\Player_LeftRun.fbx", PlayerAnimation::Player_LeftRun);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("asset\\model\\fbx\\Player_RightRun.fbx", PlayerAnimation::Player_RightRun);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("asset\\model\\fbx\\Player_BackRun.fbx", PlayerAnimation::Player_BackRun);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("asset\\model\\fbx\\Player_Attack.fbx", PlayerAnimation::Player_Attack);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("asset\\model\\fbx\\Player_Death.fbx", PlayerAnimation::Player_Death);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("asset\\model\\fbx\\Player_InPlaceJump.fbx", PlayerAnimation::Player_InPlaceJump);
        LoadAnimationModelData(FBXModel::FBXModel_Player, m_FBXModel[FBXModel::FBXModel_Player]);

        m_FBXModel[FBXModel::FBXModel_Enemy]->Load("asset\\model\\fbx\\Mutant.fbx");
        m_FBXModel[FBXModel::FBXModel_Enemy]->LoadAnimation("asset\\model\\fbx\\Mutant_Idol.fbx", EnemyAnimation::Enemy_Idle);
        m_FBXModel[FBXModel::FBXModel_Enemy]->LoadAnimation("asset\\model\\fbx\\Mutant_Run.fbx", EnemyAnimation::Enemy_Run);
        m_FBXModel[FBXModel::FBXModel_Enemy]->LoadAnimation("asset\\model\\fbx\\Mutant_Attack.fbx", EnemyAnimation::Enemy_Attack);
        m_FBXModel[FBXModel::FBXModel_Enemy]->LoadAnimation("asset\\model\\fbx\\Mutant_Damage.fbx", EnemyAnimation::Enemy_Damage);
        LoadAnimationModelData(FBXModel::FBXModel_Enemy, m_FBXModel[FBXModel::FBXModel_Enemy]);

        m_FBXModel[FBXModel::FBXModel_NPC1]->Load("asset\\model\\fbx\\GoGirl.fbx");
        m_FBXModel[FBXModel::FBXModel_NPC1]->LoadAnimation("asset\\model\\fbx\\GoGirl_Idle.fbx", NPCAnimation::NPC_Idle);
        LoadAnimationModelData(FBXModel::FBXModel_NPC1, m_FBXModel[FBXModel::FBXModel_NPC1]);
    }
    break;
    case SCENE_RESULT:
        break;
    default:
        break;
    }
}

void AnimationModelContainer::Unload(int sceneIndex)
{
    //for (auto& pair : m_AnimationModelDictionary) {
    //    if (pair.second)
    //    {
    //        delete pair.second;
    //        pair.second = nullptr;
    //    }      
    //}
    //m_AnimationModelDictionary.clear(); 


    //for (int i = 0; i < FBXModel::FBXModel_Max; i++) {
    //    if (m_FBXModel[i] != nullptr) 
    //    {
    //        delete m_FBXModel[i];
    //        m_FBXModel[i] = nullptr;
    //    }
    //}
}




AnimationModel* AnimationModelContainer::GetAnimationModel_Key(int index)
{
    auto it = m_AnimationModelDictionary.find(index);
    if (it != m_AnimationModelDictionary.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}

void AnimationModelContainer::LoadAnimationModelData(int index, AnimationModel* model)
{
    	auto it = m_AnimationModelDictionary.find(index);
        if (it == m_AnimationModelDictionary.end()) 
        {
            if (model != nullptr)
            {
			m_AnimationModelDictionary[index] = model;
		}
        else
        {
		//ロードに失敗した
        }
    }
}

