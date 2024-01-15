#pragma once
#include "gameObject.h"


//@ŒÍ‚ê‚½ó‘Ô‚ð’Ç‰Á‚·‚é‚©l‚¦‚é
enum FarmTileState
{
	EMPTY,      // ‹ó
    PLOWED,     // k‚³‚ê‚½
    PLOWEDWATERED, //…‚â‚è‚µ‚½
    MAX_GROWTH_STAGE
};

class FarmTile : public GameObject
{
private:
    FarmTileState m_FarmTile;
    class Crop* m_Crop{};

public:
	void Load();
	void Unload();
    void Init();
    void Uninit();
    void Update();
    void Draw();

    //void plow() {
    //    if (state == EMPTY) state = PLOWED;
    //}

    //void plantSeed() {
    //    if (state == PLOWED) {
    //        state = PLANTED;
    //        growthStage = 1; // ‰Šú¬’·’iŠK
    //    }
    //}

    //void updateGrowth() {
    //    if (state == PLANTED || state == GROWING) {
    //        growthStage++;
    //        if (growthStage >= FarmTileState::MAX_GROWTH_STAGE) {
    //            state = HARVESTABLE;
    //        }
    //        else {
    //            state = GROWING;
    //        }
    //    }
    //}
};


