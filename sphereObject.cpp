#include "main.h"
#include "sphereObject.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "debugmanager.h"
#include "shader.h"
#include "modelContainer.h"
#include "gameObject.h"
#include "debugmanager.h"

void SphereObject::Init()
{
	AddComponent<VertexLighting>();
	m_Model = ModelContainer::GetModelKey("Sphere");
}

void SphereObject::Update()
{

}

void SphereObject::Draw()
{
	if(!DebugManager::GetIsCollisionDrawActive()) return;
	if (m_Model == nullptr) return;
	if (m_IsEnable == false) return;


	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;

	//D3DXVec3TransformCoord(&m_WorldPosition, &m_WorldPosition, &world);//ワールド座標

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();

}
