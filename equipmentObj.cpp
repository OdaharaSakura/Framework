#include "main.h"
#include "equipmentObj.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "debugmanager.h"
#include "shader.h"
#include "iEquipment.h"
#include "equipment.h"
#include "modelContainer.h"

void EquipmentObj::Init()
{
	AddComponent<VertexLighting>();

	m_Rotation = D3DXVECTOR3(-3.14f / 4, 0.0f, -3.14f / 2);
	m_WorldPosition = D3DXVECTOR3(0.0f, 0.125f, 0.0f);
}

void EquipmentObj::Update()
{
	Scene* scene = Manager::GetScene();
	IEquipment* iEquipment = scene->GetGameObject<IEquipment>();
	if (iEquipment != nullptr)
	{
		Equipment* equipment = iEquipment->GetEquipment();
		if (equipment)
		{
			SetIsEnable(true);
			m_Model = ModelContainer::GetModelKey(equipment->GetKey());
		}
		else
		{
			SetIsEnable(false);
		}

	}

}

void EquipmentObj::Draw()
{
	if (m_Model == nullptr) return;
	if (m_IsEnable == false) return;

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixRotationYawPitchRoll(&rot, GetRotation().y + m_Rotation.y, GetRotation().x + m_Rotation.x, GetRotation().z + m_Rotation.z);
	D3DXMatrixTranslation(&trans, GetPosition().x + m_WorldPosition.x, GetPosition().y + m_WorldPosition.y, GetPosition().z + m_WorldPosition.z);
	world = scale * rot * trans * m_pMatrix * GetParent()->GetMatrix();

	//D3DXVec3TransformCoord(&m_WorldPosition, &m_WorldPosition, &world);//ワールド座標

	Renderer::SetWorldMatrix(&world);

	//#ifdef _DEBUG
	m_Model->Draw();

	//#endif
}
