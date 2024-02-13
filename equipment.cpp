#include "main.h"
#include "equipment.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "farmField.h"
#include "farmTile.h"

void Hoe::Execute()
{

	//TODO:プレイヤーとの距離をここで取得する必要なし、farmfieldの中にプレイヤーがいるかどうかの判定を行う
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();

	D3DXVECTOR3 playerPosition = m_Player->GetPosition();
	D3DXVECTOR3 playerScale = m_Player->GetScale();

	FarmField* farmField = scene->GetGameObject<FarmField>();

	D3DXVECTOR3 position = farmField->GetPosition();
	D3DXVECTOR3 scale = farmField->GetScale();

	if (position.x - scale.x - (scale.x / 2) < playerPosition.x &&
		playerPosition.x < position.x + scale.x + (scale.x / 2) &&
		position.z - scale.z - (scale.z / 2) < playerPosition.z &&
		playerPosition.z < position.z + scale.z + (scale.z / 2))
	{
		std::vector<FarmTile*> farmTiles = farmField->GetFarmTiles();
		std::vector<FarmTile*> emptyFarmTiles;

        //StateがenptyのFarmTileを取得
		for (int i = 0; i < farmTiles.size(); i++)
		{
			if (farmTiles[i]->GetFarmTileState() == FarmTileState::EMPTY)
			{
				emptyFarmTiles.push_back(farmTiles[i]);
			}
		}

		// プレイヤーと一番近いemptyFarmTileを取得（距離の二乗を利用）
		FarmTile* nearestEmptyFarmTile = nullptr;
		float nearestDistanceSq = FLT_MAX; // 初期値は非常に大きな値

		for (FarmTile* tile : emptyFarmTiles)
		{
			D3DXVECTOR3 tilePosition = tile->GetPosition();
			// プレイヤーとこのFarmTileとの距離の二乗を計算
			const D3DXVECTOR3 d = tilePosition - playerPosition;
			float distanceSq = D3DXVec3LengthSq(&d);

			// これまでの最小距離の二乗よりも短い場合は、このFarmTileを記録
			if (distanceSq < nearestDistanceSq)
			{
				nearestDistanceSq = distanceSq;
				nearestEmptyFarmTile = tile;
				
			}
		}
		if (nearestEmptyFarmTile != nullptr)
		{
			nearestEmptyFarmTile->Plow();
			m_Player->AddHp(-m_LostHP);
		}
	}	
}

void Sickle::Execute()
{
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();

	FarmField* farmField = scene->GetGameObject<FarmField>();
}
