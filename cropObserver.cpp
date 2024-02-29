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
	if (m_FarmTile->GetFarmTileState() == FarmTileState::PLANTED_WATERED) { // FarmTileが水やりされている状態であるかチェック
		 int firstGrowTime = m_Crop->GetGrowthTimeToFirstState();

		m_Minute += 10; // 分を加算
		m_Hour = m_Minute / 60; // 時間を更新
		if (m_Hour >= m_Crop->GetGrowthTimeToFirstState() && m_Crop->GetCropState() == CropState::Seed) 
		{ // 最初の成長段階に達したかチェック		
			m_FarmTile->AdvanceCropState(); 
		}

		if (m_Hour >= m_Crop->GetGrowthTime() && m_Crop->GetCropState() == CropState::Seedling1)
		{ // 収穫可能な状態に達したかチェック
			m_FarmTile->AdvanceCropState(); 
		}
	}
}

