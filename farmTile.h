#pragma once
#include "gameObject.h"


//Å@åÕÇÍÇΩèÛë‘Çí«â¡Ç∑ÇÈÇ©çlÇ¶ÇÈ
enum FarmTileState
{
	EMPTY,      // ãÛ
    PLOWED,     // çkÇ≥ÇÍÇΩ
    WATERED, //êÖÇ‚ÇËÇµÇΩ
    PLANTED,    // éÌÇêAÇ¶ÇΩ
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


