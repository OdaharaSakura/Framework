#pragma once
#include "gameObject.h"


//Å@åÕÇÍÇΩèÛë‘Çí«â¡Ç∑ÇÈÇ©çlÇ¶ÇÈ
enum FarmTileState
{
	EMPTY,      // ãÛ
    PLOWED,     // çkÇ≥ÇÍÇΩ
    PLOWEDWATERED, //êÖÇ‚ÇËÇµÇΩ
    MAX_FARMTILE_STAGE
};

class FarmTile : public GameObject
{
private:
    FarmTileState m_FarmTileState{};
    class Crop* m_Crop{};
    class Model* m_Model[MAX_FARMTILE_STAGE]{}; //

    int num{};

public:
	void Load();
	void Unload();
    void Init();
    void Uninit();
    void Update();
    void Draw();
};


