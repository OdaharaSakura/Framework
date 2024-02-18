#pragma once
#include "gameObject.h"


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
    class Crop* m_Crop{};
    class Model* m_FarmTileModel{}; 
    class Model* m_CropModel{};

    int num{};

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

    FarmTileState GetFarmTileState() { return m_FarmTileState; }

    void Plow();
    void Water();
    void PlantCrop(class Crop* crop);
    void Harvest();
};


