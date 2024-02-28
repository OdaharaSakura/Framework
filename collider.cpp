
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "collider.h"
#include "collision.h"
#include "sphereObject.h"
#include "gameObject.h"
#include "model.h"



void SphereCollider::Init()
{
	Scene* scene = Manager::GetScene();
	m_SphereObj = scene->AddGameObject<SphereObject>(LAYER_SPHERECOLLIDER);//colliderを作るオブジェクトの生成
	m_SphereObj->SetParent(m_AttachObject);//親子関係を設定
	m_SphereObj->SetScale(D3DXVECTOR3(m_Radius, m_Radius, m_Radius) * m_ScaleOffset);
	m_SphereObj->SetPosition(m_WorldPosition);
	m_SphereObj->SetRadius(m_Radius);
	SetIsStatic(false);

}


void SphereCollider::Uninit()
{
//#ifdef _DEBUG
	//if(m_VertexBuffer != nullptr)m_VertexBuffer->Release();*/

//#endif
}


void SphereCollider::Update()
{
	m_SphereObj->SetScale(D3DXVECTOR3(m_Radius, m_Radius, m_Radius) * m_ScaleOffset);
	m_SphereObj->SetPosition(m_WorldPosition);
}


void SphereCollider::Draw()
{



}