#include "main.h"
#include "equipment.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "farmField.h"
#include "farmTile.h"

void Hoe::Execute()
{

	//TODO:�v���C���[�Ƃ̋����������Ŏ擾����K�v�Ȃ��Afarmfield�̒��Ƀv���C���[�����邩�ǂ����̔�����s��
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

        //State��enpty��FarmTile���擾
		for (int i = 0; i < farmTiles.size(); i++)
		{
			if (farmTiles[i]->GetFarmTileState() == FarmTileState::EMPTY)
			{
				emptyFarmTiles.push_back(farmTiles[i]);
			}
		}

		// �v���C���[�ƈ�ԋ߂�emptyFarmTile���擾�i�����̓��𗘗p�j
		FarmTile* nearestEmptyFarmTile = nullptr;
		float nearestDistanceSq = FLT_MAX; // �����l�͔��ɑ傫�Ȓl

		for (FarmTile* tile : emptyFarmTiles)
		{
			D3DXVECTOR3 tilePosition = tile->GetPosition();
			// �v���C���[�Ƃ���FarmTile�Ƃ̋����̓����v�Z
			const D3DXVECTOR3 d = tilePosition - playerPosition;
			float distanceSq = D3DXVec3LengthSq(&d);

			// ����܂ł̍ŏ������̓������Z���ꍇ�́A����FarmTile���L�^
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
