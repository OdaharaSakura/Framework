#pragma once

#include "main.cpp"
#include "renderer.h"
#include "animationModel.h"
#include "model.h"

class ModelContainer
{
public:
	enum LoadFBXModels
	{
		PLAYER_MODEL,
		READ_MODEL_FBX_MAX
	};

	enum LoadOBJModels
	{
		READ_MODEL_OBJ_MAX
	};

private:
	static AnimationModel* ModelsFBX[ModelContainer::READ_MODEL_FBX_MAX];
	static std::unordered_map<std::string, const aiScene*> m_Animation;

public:
	static void LoadModels()
	{
		//FBXModels
		ModelsFBX[ModelContainer::PLAYER_MODEL]->Load("asset\\model\\fbx\\Player.fbx");

		//Animations
		m_Animation["Idol"] = aiImportFile("asset\\model\\fbx\\Player_Idle.fbx", aiProcess_ConvertToLeftHanded);
		assert(m_Animation["Idol"]);


		//m_Model->LoadAnimation("asset\\model\\fbx\\Player_Run.fbx", "Run");
		//m_Model->LoadAnimation("asset\\model\\fbx\\Player_LeftRun.fbx", "LeftRun");
		//m_Model->LoadAnimation("asset\\model\\fbx\\Player_RightRun.fbx", "RightRun");
		//m_Model->LoadAnimation("asset\\model\\fbx\\Player_BackRun.fbx", "BackRun");
		//m_Model->LoadAnimation("asset\\model\\fbx\\Player_Attack.fbx", "Attack");
		//m_Model->LoadAnimation("asset\\model\\fbx\\Player_Death.fbx", "Death");
		//m_Model->LoadAnimation("asset\\model\\fbx\\Player_InPlaceJump.fbx", "InPlaceJump");
	}

};