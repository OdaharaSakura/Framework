#include "main.h"
#include "renderer.h"
#include "house.h"
#include "shader.h"


void House::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\obj\\House.obj");

	m_Rotation = D3DXVECTOR3(0.0f, 3.14f / 2 * 3, 0.0f);

	AddComponent<VertexLighting>();
}

void House::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}

void House::Update()
{

}

void House::Draw()
{

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
