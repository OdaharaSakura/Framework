#pragma once

#include "animationModel.h"
#include <unordered_map>
#include <string>

enum FBXModel
{
	FBXModel_ResultPlayer,
	FBXModel_Player,
	FBXModel_Enemy,
	FBXModel_NPC1,
	FBXModel_Max
};

enum PlayerAnimation
{
	Player_Idle,
	Player_Run,
	Player_LeftRun,
	Player_RightRun,
	Player_BackRun,
	Player_Attack,
	Player_Death,
	Player_InPlaceJump
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
	static std::unordered_map<int, AnimationModel*> m_AnimationModelDictionary;//キー + Image

	static std::string m_FBXAnimationsFrontPath;//ファイルのパス

	static AnimationModel* m_FBXModel[FBXModel::FBXModel_Max];


public:

	//sceneによってどれを読み込むかを決める
	static void Load(int sceneIndex);
	static void Unload(int sceneIndex);


	static AnimationModel* GetAnimationModel_Key(int index);

	static void LoadAnimationModelData(int index, AnimationModel* model);
};