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
	if(time != nullptr)time->RemoveObserver(this);
}

void CropObserver::UpdateMinute()
{
	if (m_FarmTile->GetFarmTileState() == FarmTileState::PLANTED_WATERED) { // FarmTile������肳��Ă����Ԃł��邩�`�F�b�N
		 int firstGrowTime = m_Crop->GetGrowthTimeToFirstState();

		m_Minute += 10; // �������Z
		m_Hour = m_Minute / 60; // ���Ԃ��X�V
		if (m_Hour >= m_Crop->GetGrowthTimeToFirstState() && m_Crop->GetCropState() == CropState::Seed) 
		{ // �ŏ��̐����i�K�ɒB�������`�F�b�N		
			m_FarmTile->AdvanceCropState(); 
		}

		if (m_Hour >= m_Crop->GetGrowthTime() && m_Crop->GetCropState() == CropState::Seedling1)
		{ // ���n�\�ȏ�ԂɒB�������`�F�b�N
			m_FarmTile->AdvanceCropState(); 
		}
	}
}

