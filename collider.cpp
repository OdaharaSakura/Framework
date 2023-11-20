
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "collider.h"
#include "collision.h"
#include "testObj.h"
#include "gameObject.h"
#include "model.h"



void SphereCollider::Init()
{
	//Collision::m_SphereColliderObjects.push_back(m_AttachGameObject);
	
	m_testObj = Manager::GetScene()->AddGameObject<TestObj>(COLLIDER_LAYER);

	m_testObj->SetScale(D3DXVECTOR3(m_Radius, m_Radius, m_Radius) * m_ScaleOffset);

	m_Scale = D3DXVECTOR3(m_Radius, m_Radius, m_Radius);

//#ifdef _DEBUG

//#endif
}


void SphereCollider::Uninit()
{
//#ifdef _DEBUG
	/*if(m_VertexBuffer != nullptr)m_VertexBuffer->Release();*/


//#endif
}


void SphereCollider::Update()
{
	m_testObj->SetScale(D3DXVECTOR3(m_Radius, m_Radius, m_Radius) * m_ScaleOffset);
}


void SphereCollider::Draw()
{



}