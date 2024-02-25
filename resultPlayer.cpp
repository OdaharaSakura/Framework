#include "main.h"
#include "renderer.h"
#include "resultplayer.h"
#include "input.h"
#include "bullet.h"
#include "manager.h"
#include "scene.h"
#include "cylinder.h"
#include "enemy.h"
#include "gauge.h"
#include "box.h"
#include "audio.h"
#include "shadow.h"
#include "animationModel.h"
#include "result.h"
#include "earth.h"
#include "shader.h"
#include "animationModelContainer.h"


void ResultPlayer::Init()
{
	Scene* scene = Manager::GetScene();

	m_Model = AnimationModelContainer::GetAnimationModel_Key(FBXModel::FBXModel_ResultPlayer);



	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	AddComponent<PercentageCloserFiltering>();

}

void ResultPlayer::Uninit()
{
	GameObject::Uninit();
	m_Model->Unload();
	delete m_Model;


}

void ResultPlayer::Update()
{
	//GameObject::Update();
	Scene* scene = Manager::GetScene();


	m_AnimeFrame++;
	m_BlendRate += 0.01f;

}

void ResultPlayer::Draw()
{
	//GameObject::Draw();

	// マトリクス設定
	D3DXMATRIX matrix, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//モデルによるが、後ろ向いてたら+ D3DX_PIで180度回転させる
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	matrix = scale * rot * trans;
	m_Matrix = matrix;

	Renderer::SetWorldMatrix(&matrix);

	m_Model->Update(PlayerAnimation::Player_Idle, m_AnimeFrame, PlayerAnimation::Player_Idle, m_AnimeFrame, m_BlendRate);
	

	m_Model->Draw();
}

