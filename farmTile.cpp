#include "main.h"
#include "farmTile.h"
#include "renderer.h"
#include "model.h"
#include "shader.h"

#include "modelContainer.h"
#include "cropObserver.h"
#include "scene.h"
#include "manager.h"
#include "inventory.h"
#include "itemFactory.h"
#include "staticObject.h"
#include "gameObject.h"

void FarmTile::Init()
{
	m_Scale = D3DXVECTOR3(0.7f, 0.7f, 0.7f);

	AddComponent<PixelLighting>();

	m_FarmTileState = FarmTileState::EMPTY;

	Scene* scene = Manager::GetScene();
	m_CropStaticObject = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	m_CropStaticObject->SetPosition(D3DXVECTOR3(m_WorldPosition.x, 0.2f, m_WorldPosition.z));
}

void FarmTile::Uninit()
{
	////TODO:ここエラー吐く、要改善
	//if (m_FarmTileModel != nullptr)
	//{
	//	m_FarmTileModel->Unload();
	//	delete m_FarmTileModel;
	//}

	//if (m_CropStaticObject != nullptr)
	//{
	//	m_CropStaticObject->Unload();
	//	delete m_CropStaticObject;
	//}
}

void FarmTile::Update()
{
	m_CropStaticObject->SetPosition(D3DXVECTOR3(m_WorldPosition.x, 0.2f, m_WorldPosition.z));
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
	if(m_CropStaticObject) m_CropStaticObject->Draw();
}

void FarmTile::Plow()
{
	m_FarmTileState = FarmTileState::PLOWED;
	m_FarmTileModel = ModelContainer::GetModelKey("DryField");
}

void FarmTile::Water()
{
	if (m_FarmTileState == FarmTileState::PLOWED)
	{
		m_FarmTileState = FarmTileState::WATERED;
	}
	if (m_FarmTileState == FarmTileState::PLANTED)
	{
		m_FarmTileState = FarmTileState::PLANTED_WATERED;
	}
	m_FarmTileModel = ModelContainer::GetModelKey("WetField");
}

void FarmTile::PlantCrop(Crop* crop)
{
	if (m_FarmTileState == FarmTileState::PLOWED)
	{
		m_FarmTileState = FarmTileState::PLANTED;
	}
	if (m_FarmTileState == FarmTileState::WATERED)
	{
		m_FarmTileState = FarmTileState::PLANTED_WATERED;
	}
	m_Crop = crop;
	m_CropObserver = new CropObserver(this, crop);
	AdvanceCropState();
}

void FarmTile::Harvest()
{
	Scene* scene = Manager::GetScene();
	Inventory* inventory = scene->GetGameObject<Inventory>();
	ItemFactory* itemFactory = new ItemFactory();
	auto crop = itemFactory->CreateItem(m_Crop->GetKey());
	inventory->AddItem(crop);
	m_FarmTileState = FarmTileState::EMPTY;
	delete m_CropObserver;
	m_CropObserver = nullptr;
	delete m_FarmTileModel;
	m_FarmTileModel = nullptr;
	delete m_CropStaticObject;
	m_CropStaticObject = nullptr;
	delete m_Crop;
	m_Crop = nullptr;
}

void FarmTile::AdvanceCropState()
{
	if(m_CropStaticObject == nullptr) return;
	switch (m_Crop->GetCropState())
	{
	case CropState::None:
		m_Crop->SetCropState(CropState::Seed);
		m_CropStaticObject->SetModel_Key("Seed");
		break;
	case CropState::Seed:
		m_Crop->SetCropState(CropState::Seedling1);
		m_CropStaticObject->SetModel_Key(m_Crop->GetFirstStateModelPass());
		break;
	case CropState::Seedling1:
		m_Crop->SetCropState(CropState::Harvest);
		m_CropStaticObject->SetModel_Key(m_Crop->GetHarvestModelPass());
		break;
	case CropState::Harvest:
		m_Crop->SetCropState(CropState::None);
		m_CropStaticObject->SetModel_Null();
		break;
	}
}

CropState FarmTile::GetCropState()
{
	if (m_Crop) return m_Crop->GetCropState();
}
