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
	if (m_FarmTile->GetFarmTileState() == FarmTileState::PLANTED_WATERED) { // FarmTileが水やりされている状態であるかチェック
		m_Hour++; // 時間を加算
		if (m_Hour >= m_Crop->GetGrowthTimeToFirstState()) { // 最初の成長段階に達したかチェック
					m_FarmTile->AdvanceCropState(); // FarmTileの成長段階を進める
				}
		if (m_Hour >= m_Crop->GetGrowthTime()) { // 収穫可能な状態に達したかチェック
		
			m_FarmTile->AdvanceCropState(); // FarmTileの成長段階を進める
				}
	}
}
