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


void ResultPlayer::Init()
{
	Scene* scene = Manager::GetScene();
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\fbx\\Player.fbx");
	m_Model->LoadAnimation("asset\\model\\fbx\\Player_Idle.fbx", "Idol");


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


	m_AnimeState = IDOL;

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

	m_Model->Update("Idol", m_AnimeFrame, "Idol", m_AnimeFrame, m_BlendRate);
	

	m_Model->Draw();
}

