#include "cropObserver.h"
#include "crop.h"
#include "farmTile.h"
#include "time.h"
#include "scene.h"
#include "manager.h"

CropObserver::CropObserver(FarmTile* farmTile, Crop* crop)
{
	m_Crop = crop;
	m_FarmTile = farmTile;

	Scene* scene = Manager::GetScene();
	Time * time = scene->GetGameObject<Time>();
	time->AddObserver(this);
}

CropObserver::~CropObserver()
{
	Scene* scene = Manager::GetScene();
	Time * time = scene->GetGameObject<Time>();
	time->RemoveObserver(this);
}

void CropObserver::Update()
{
	if (m_FarmTile->GetFarmTileState() == FarmTileState::PLANTED_WATERED) { // FarmTile������肳��Ă����Ԃł��邩�`�F�b�N
		m_Hour++; // ���Ԃ����Z
		if (m_Hour >= m_Crop->GetGrowthTimeToFirstState()) { // �ŏ��̐����i�K�ɒB�������`�F�b�N
					m_FarmTile->AdvanceCropState(); // FarmTile�̐����i�K��i�߂�
				}
		if (m_Hour >= m_Crop->GetGrowthTime()) { // ���n�\�ȏ�ԂɒB�������`�F�b�N
		
			m_FarmTile->AdvanceCropState(); // FarmTile�̐����i�K��i�߂�
				}
	}
}
