#include "main.h"
#include "renderer.h"
#include "animationModelContainer.h"
#include "scene.h"
#include <algorithm>


std::unordered_map<int, AnimationModel*> AnimationModelContainer::m_AnimationModelDictionary{};

AnimationModel* AnimationModelContainer::m_FBXModel[FBXModel::FBXModel_Max] = { new AnimationModel()};



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
        m_FBXModel[FBXModel::FBXModel_Player]->Load("Player.fbx");
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Idle.fbx", PlayerAnimation::Player_Idle);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Run.fbx", PlayerAnimation::Player_Run);
        LoadAnimationModelData(FBXModel::FBXModel_Player, m_FBXModel[FBXModel::FBXModel_Player]);
        break;
    case SCENE_GAME:
    {
        m_FBXModel[FBXModel::FBXModel_Player]->Load("Player.fbx");
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Idle.fbx", PlayerAnimation::Player_Idle);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Run.fbx", PlayerAnimation::Player_Run);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_LeftRun.fbx", PlayerAnimation::Player_LeftRun);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_RightRun.fbx", PlayerAnimation::Player_RightRun);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_BackRun.fbx", PlayerAnimation::Player_BackRun);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Attack.fbx", PlayerAnimation::Player_Attack);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Death.fbx", PlayerAnimation::Player_Death);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_InPlaceJump.fbx", PlayerAnimation::Player_InPlaceJump);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Plowing.fbx", PlayerAnimation::Player_Plowing);
        LoadAnimationModelData(FBXModel::FBXModel_Player, m_FBXModel[FBXModel::FBXModel_Player]);

        m_FBXModel[FBXModel::FBXModel_Enemy]->Load("Mutant.fbx");
        m_FBXModel[FBXModel::FBXModel_Enemy]->LoadAnimation("Mutant_Idol.fbx", EnemyAnimation::Enemy_Idle);
        m_FBXModel[FBXModel::FBXModel_Enemy]->LoadAnimation("Mutant_Run.fbx", EnemyAnimation::Enemy_Run);
        m_FBXModel[FBXModel::FBXModel_Enemy]->LoadAnimation("Mutant_Attack.fbx", EnemyAnimation::Enemy_Attack);
        m_FBXModel[FBXModel::FBXModel_Enemy]->LoadAnimation("Mutant_Damage.fbx", EnemyAnimation::Enemy_Damage);
        LoadAnimationModelData(FBXModel::FBXModel_Enemy, m_FBXModel[FBXModel::FBXModel_Enemy]);

        m_FBXModel[FBXModel::FBXModel_NPC1]->Load("GoGirl.fbx");
        m_FBXModel[FBXModel::FBXModel_NPC1]->LoadAnimation("GoGirl_Idle.fbx", NPCAnimation::NPC_Idle);
        LoadAnimationModelData(FBXModel::FBXModel_NPC1, m_FBXModel[FBXModel::FBXModel_NPC1]);

        m_FBXModel[FBXModel::FBXModel_Cow]->Load("cowpose.fbx");
        m_FBXModel[FBXModel::FBXModel_Cow]->LoadAnimation("cowanime.fbx", CowAnimation::Cow_Walk);
        LoadAnimationModelData(FBXModel::FBXModel_Cow, m_FBXModel[FBXModel::FBXModel_Cow]);
    }
    break;
    case SCENE_HOUSEROOM:
        m_FBXModel[FBXModel::FBXModel_Player]->Load("Player.fbx");
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Idle.fbx", PlayerAnimation::Player_Idle);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Run.fbx", PlayerAnimation::Player_Run);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_LeftRun.fbx", PlayerAnimation::Player_LeftRun);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_RightRun.fbx", PlayerAnimation::Player_RightRun);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_BackRun.fbx", PlayerAnimation::Player_BackRun);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Attack.fbx", PlayerAnimation::Player_Attack);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Death.fbx", PlayerAnimation::Player_Death);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_InPlaceJump.fbx", PlayerAnimation::Player_InPlaceJump);
        m_FBXModel[FBXModel::FBXModel_Player]->LoadAnimation("Player_Plowing.fbx", PlayerAnimation::Player_Plowing);
        LoadAnimationModelData(FBXModel::FBXModel_Player, m_FBXModel[FBXModel::FBXModel_Player]);
        break;

    case SCENE_RESULT:
        break;
    default:
        break;
    }
}

void AnimationModelContainer::Unload(int sceneIndex)
{
    for (auto& pair : m_AnimationModelDictionary) {
        if (pair.second)
        {
            pair.second->Unload();
            delete pair.second;
            pair.second = nullptr;
        }      
    }
    m_AnimationModelDictionary.clear(); 


    for (int i = 0; i < FBXModel::FBXModel_Max; i++) {
        if (m_FBXModel[i] != nullptr) 
        {
            m_FBXModel[i] = nullptr;
        }
    }
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

