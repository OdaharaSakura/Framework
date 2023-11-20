#pragma once

#include <unordered_map>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#include "animationModel.h"
#include <cassert>
#pragma comment (lib, "assimp-vc143-mt.lib")



class LoadModel
{
public:
	enum LoadFBXModels
	{
		PLAYER_MODEL,
		READ_MODEL_FBX_MAX
	};

private:
	static AnimationModel ModelsFBX[LoadModel::READ_MODEL_FBX_MAX];
	static std::unordered_map<std::string, const aiScene*> m_Animation;

public:
	static void LoadModels()
	{
		//FBXModels
		ModelsFBX->Load("asset\\model\\Player.fbx");

		//Animations
		m_Animation["Idol"] = aiImportFile("asset\\model\\Player_Idle.fbx", aiProcess_ConvertToLeftHanded);
		
		
		assert(m_Animation["Idol"]);

		
		m_Model->LoadAnimation("asset\\model\\Player_Run.fbx", "Run");
		m_Model->LoadAnimation("asset\\model\\Player_LeftRun.fbx", "LeftRun");
		m_Model->LoadAnimation("asset\\model\\Player_RightRun.fbx", "RightRun");
		m_Model->LoadAnimation("asset\\model\\Player_BackRun.fbx", "BackRun");
		m_Model->LoadAnimation("asset\\model\\Player_Attack.fbx", "Attack");
		m_Model->LoadAnimation("asset\\model\\Player_Death.fbx", "Death");
		m_Model->LoadAnimation("asset\\model\\Player_InPlaceJump.fbx", "InPlaceJump");
	}
	
};