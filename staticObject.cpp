
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "model.h"
#include "staticObject.h"
#include "modelContainer.h"
#include "shader.h"



void StaticObject::Init()
{
	m_IsStatic = true;

}

void StaticObject::Uninit()
{


}

void StaticObject::Update()
{

}

void StaticObject::Draw()
{
	if(m_Model == nullptr) return;
	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}

void StaticObject::SetModel_Key(std::string model_Key)
{
	m_Model = ModelContainer::GetModel_Key(model_Key);
	AddComponent<PixelLighting>();
}
