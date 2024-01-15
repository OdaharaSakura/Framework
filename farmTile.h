#pragma once
#include "gameObject.h"


//�@�͂ꂽ��Ԃ�ǉ����邩�l����
enum FarmTileState
{
	EMPTY,      // ��
    PLOWED,     // �k���ꂽ
    PLOWEDWATERED, //����肵��
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
    //        growthStage = 1; // ���������i�K
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


