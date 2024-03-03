#include "main.h"
#include "equipment.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "farmField.h"
#include "farmTile.h"
#include "cropFactory.h"
#include "enemy.h"
#include "inventory.h"
#include "iEquipment.h"

void Hoe::Execute()
{
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();
	FarmField* farmField = scene->GetGameObject<FarmField>();
	auto farmTile = farmField->GetFarmTileClosestToPlayer(FarmTileState::EMPTY);
	if (farmTile != nullptr && m_Player->GetPlayerState() == PLAYER_STATE::PLAYER_STATE_GROUND)
	{
		farmTile->Plow();
		m_Player->AddHp(-m_LostHP);
		m_Player->SetPlayerState(PLAYER_STATE::PLAYER_STATE_PLOW);
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
	if (farmTile != nullptr && m_Player->GetPlayerState() == PLAYER_STATE::PLAYER_STATE_GROUND)
	{
		farmTile->Water();
		m_Player->AddHp(-m_LostHP);
		m_Player->SetPlayerState(PLAYER_STATE::PLAYER_STATE_PLOW);
	}
}

void TomatoSeed::Execute()
{
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();
	FarmField* farmField = scene->GetGameObject<FarmField>();
	CropFactory* cropFactory = new CropFactory();
	Inventory* inventory = scene->GetGameObject<Inventory>();
	IEquipment* equipment = scene->GetGameObject<IEquipment>();
	auto farmTile = farmField->GetFarmTileClosestToPlayer(FarmTileState::PLOWED, FarmTileState::WATERED);
	if (farmTile != nullptr && m_Player->GetPlayerState() == PLAYER_STATE::PLAYER_STATE_GROUND)
	{
		inventory->DecreaseItem("TomatoSeed");

		auto crop = cropFactory->CreateCrop("Tomato");
		farmTile->PlantCrop(crop);
		m_Player->AddHp(-m_LostHP);
		m_Player->SetPlayerState(PLAYER_STATE::PLAYER_STATE_PLOW);
	}

	if (inventory->GetItem("TomatoSeed") == nullptr)
	{
		equipment->RemoveEquipment();
	}
}

void CarrotSeed::Execute()
{
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();
	FarmField* farmField = scene->GetGameObject<FarmField>();
	CropFactory* cropFactory = new CropFactory();
	Inventory* inventory = scene->GetGameObject<Inventory>();
	IEquipment* equipment = scene->GetGameObject<IEquipment>();
	auto farmTile = farmField->GetFarmTileClosestToPlayer(FarmTileState::PLOWED, FarmTileState::WATERED);
	if (farmTile != nullptr && m_Player->GetPlayerState() == PLAYER_STATE::PLAYER_STATE_GROUND)
	{
		inventory->DecreaseItem("CarrotSeed");

		auto crop = cropFactory->CreateCrop("Carrot");
		farmTile->PlantCrop(crop);
		m_Player->AddHp(-m_LostHP);
		m_Player->SetPlayerState(PLAYER_STATE::PLAYER_STATE_PLOW);
	}

	if (inventory->GetItem("CarrotSeed") == nullptr)
	{
		equipment->RemoveEquipment();
	}
}

void Sword::Execute()
{
	Scene* scene = Manager::GetScene();
	auto enemies = scene->GetGameObjects<Enemy>();
	m_Player = scene->GetGameObject<Player>();
	if (enemies.size() <= 0) return;

	for (Enemy* enemy : enemies)
	{
		if (enemy->GetDamageflg() && m_Player->GetPlayerState() == PLAYER_STATE::PLAYER_STATE_GROUND)
		{
			enemy->AddHp(-50);
			m_Player->AddHp(-m_LostHP);
			m_Player->SetPlayerState(PLAYER_STATE::PLAYER_STATE_ATTACK);
		}
	}


}
