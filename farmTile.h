#pragma once
#include "gameObject.h"
#include "crop.h"

//@ŒÍ‚ê‚½ó‘Ô‚ğ’Ç‰Á‚·‚é‚©l‚¦‚é
enum FarmTileState
{
	EMPTY = 0,      // ‹ó
    PLOWED,     // k‚³‚ê‚½
    WATERED, //…‚â‚è‚µ‚½
    PLANTED,    // í‚ğA‚¦‚½
    PLANTED_WATERED, //í‚ğA‚¦‚Ä…‚â‚è‚µ‚½
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