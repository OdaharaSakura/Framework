#pragma once
#include "gameObject.h"
#include "crop.h"

//　枯れた状態を追加するか考える
enum FarmTileState
{
	EMPTY = 0,      // 空
    PLOWED,     // 耕された
    WATERED, //水やりした
    PLANTED,    // 種を植えた
    PLANTED_WATERED, //種を植えて水やりした
    MAX_FARMTILE_STAGE
};

class FarmTile : public GameObject
{
private:
    FarmTileState m_FarmTileState{};
    Crop* m_Crop{};
    class Model* m_FarmTileModel{}; 
    class StaticObject* m_CropStaticObject{};
    class CropObserver* m_CropObserver{};

    int num{};

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

    void Plow();
    void Water();
    void PlantCrop(Crop* crop);
    void Harvest();

    void AdvanceCropState();


    FarmTileState GetFarmTileState() { return m_FarmTileState; }
    CropState GetCropState();
    std::string GetCropKey();
    int GetCropGrowTime();

    void SetFarmTileState(FarmTileState farmTileState) { m_FarmTileState = farmTileState; }
    
    void LoadData(FarmTileState farmTileState, CropState cropState, std::string cropKey, int cropGrowTime);
};