#pragma once

#include "animationModel.h"
#include <unordered_map>
#include <string>

//�ǂݍ���FBX���f���̎��
enum FBXModel
{
	FBXModel_Player,
	FBXModel_Enemy,
	FBXModel_NPC1,
	FBXModel_Cow,
	FBXModel_Max
};

//�A�j���[�V�����C���f�b�N�X
enum PlayerAnimation
{
	Player_Idle,
	Player_Run,
	Player_LeftRun,
	Player_RightRun,
	Player_BackRun,
	Player_Attack,
	Player_Death,
	Player_InPlaceJump,
	Player_Plowing
};

enum EnemyAnimation
{
	Enemy_Idle,
	Enemy_Run,
	Enemy_Damage,
	Enemy_Attack,
	Enemy_Death,
	Enemy_InPlaceJump
};

enum NPCAnimation
{
	NPC_Idle
};

enum CowAnimation
{
	Cow_Idle,
	Cow_Walk
};

class AnimationModelContainer
{
private:
	static std::unordered_map<int, AnimationModel*> m_AnimationModelDictionary;//�L�[ + Image

	static AnimationModel* m_FBXModel[FBXModel::FBXModel_Max];


public:

	//scene�ɂ���Ăǂ��ǂݍ��ނ������߂�
	static void Load(int sceneIndex);
	static void Unload(int sceneIndex);


	static AnimationModel* GetAnimationModel_Key(int index);

	static void LoadAnimationModelData(int index, AnimationModel* model);
};