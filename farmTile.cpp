#include "main.h"
#include "farmTile.h"
#include "renderer.h"
#include "model.h"
#include "shader.h"
#include "crop.h"
#include "modelContainer.h"


void FarmTile::Init()
{
	m_Scale = D3DXVECTOR3(0.7f, 0.7f, 0.7f);

	AddComponent<VertexLighting>();
	AddComponent<PixelLighting>();

	m_FarmTileState = FarmTileState::EMPTY;
}

void FarmTile::Uninit()
{
	////TODO:ここエラー吐く、要改善
	//if (m_FarmTileModel != nullptr)
	//{
	//	m_FarmTileModel->Unload();
	//	delete m_FarmTileModel;
	//}

	//if (m_CropModel != nullptr)
	//{
	//	m_CropModel->Unload();
	//	delete m_CropModel;
	//}
}

void FarmTile::Update()
{

}

void FarmTile::Draw()
{
	if(m_FarmTileModel == nullptr) return;
	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);	

	m_FarmTileModel->Draw();
	if(m_CropModel) m_CropModel->Draw();
}

void FarmTile::Plow()
{
	m_FarmTileState = FarmTileState::PLOWED;
	m_FarmTileModel = ModelContainer::GetModelKey("DryField");
}

void FarmTile::Water()
{
	m_FarmTileState = FarmTileState::WATERED;
	m_FarmTileModel = ModelContainer::GetModelKey("WetField");
}

void FarmTile::PlantCrop(Crop* crop)
{
	m_FarmTileState = FarmTileState::PLANTED;
	//m_CropModel = ModelContainer::GetModelKey(crop->GetModelKey());
	//m_Crop = crop;
}

void FarmTile::Harvest()
{
	m_FarmTileState = FarmTileState::EMPTY;
	delete m_FarmTileModel;
	m_FarmTileModel = nullptr;
	delete m_CropModel;
	m_CropModel = nullptr;
	delete m_Crop;
	m_Crop = nullptr;
}
