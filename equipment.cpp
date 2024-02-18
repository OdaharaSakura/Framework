#include "main.h"
#include "equipment.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "farmField.h"
#include "farmTile.h"
#include "cropFactory.h"

void Hoe::Execute()
{
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();
	FarmField* farmField = scene->GetGameObject<FarmField>();
	auto farmTile = farmField->GetFarmTileClosestToPlayer(FarmTileState::EMPTY);
	if (farmTile != nullptr)
	{
		farmTile->Plow();
		m_Player->AddHp(-m_LostHP);
	}
}

void Sickle::Execute()
{
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();

	FarmField* farmField = scene->GetGameObject<FarmField>();
}

void WaterWand::Execute()
{
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();
	FarmField* farmField = scene->GetGameObject<FarmField>();
	auto farmTile = farmField->GetFarmTileClosestToPlayer(FarmTileState::PLOWED, FarmTileState::PLANTED);
	if (farmTile != nullptr)
	{
		farmTile->Water();
		m_Player->AddHp(-m_LostHP);
	}
}

void TomatoSeed::Execute()
{
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();
	FarmField* farmField = scene->GetGameObject<FarmField>();
	CropFactory* cropFactory = new CropFactory();
	auto farmTile = farmField->GetFarmTileClosestToPlayer(FarmTileState::PLOWED, FarmTileState::WATERED);
	if (farmTile != nullptr)
	{
		auto crop = cropFactory->CreateCrop("Tomato");
		farmTile->PlantCrop(crop);
		m_Player->AddHp(-m_LostHP);
	}
}

void CarrotSeed::Execute()
{
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();
	FarmField* farmField = scene->GetGameObject<FarmField>();
	CropFactory* cropFactory = new CropFactory();
	auto farmTile = farmField->GetFarmTileClosestToPlayer(FarmTileState::PLOWED, FarmTileState::WATERED);
	if (farmTile != nullptr)
	{
		auto crop = cropFactory->CreateCrop("Carrot");
		farmTile->PlantCrop(crop);
		m_Player->AddHp(-m_LostHP);
	}
}
