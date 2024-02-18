#pragma once
#include "gameObject.h"
#include "crop.h"

//@ŒÍ‚ê‚½ó‘Ô‚ğ’Ç‰Á‚·‚é‚©l‚¦‚é
enum FarmTileState
{
	EMPTY,      // ‹ó
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

    FarmTileState GetFarmTileState() { return m_FarmTileState; }

    void Plow();
    void Water();
    void PlantCrop(Crop* crop);
    void Harvest();

    void AdvanceCropState();

    CropState GetCropState();
};


