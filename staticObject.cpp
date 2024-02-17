
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "model.h"
#include "staticObject.h"
#include "modelContainer.h"
#include "shader.h"
#include "camera.h"


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
	//視錘台カリング
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	D3DXVECTOR3 length = D3DXVECTOR3(m_Scale.x, 0.0f, m_Scale.z);
	float objectSize = D3DXVec3Length(&length);

	if (!camera->CheckViewWithBoundingSphere(m_WorldPosition, objectSize))
	{
		return;
	}

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
	m_Model = ModelContainer::GetModelKey(model_Key);
	AddComponent<PixelLighting>();
}
