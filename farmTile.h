#pragma once
#include <string>

//�@�͂ꂽ��Ԃ�ǉ����邩�l����
enum FarmTileState
{
    EMPTY, 
    PLOWED,     // �k���ꂽ
    PLANTED,    // ���A����
    PLANTEDWATERED, // ���A���Đ���肵��
    GROWING,    // ������
    GROWINGWATERED, // �������Ő���肵��
    HARVESTABLE, // ���n�\
    MAX_GROWTH_STAGE
};

class FarmTile 
{
private:
    FarmTileState state;
    int growthStage;
public:
    
    FarmTile() : state(EMPTY), growthStage(0) {}

    void plow() {
        if (state == EMPTY) state = PLOWED;
    }

    void plantSeed() {
        if (state == PLOWED) {
            state = PLANTED;
            growthStage = 1; // ���������i�K
        }
    }

    void updateGrowth() {
        if (state == PLANTED || state == GROWING) {
            growthStage++;
            if (growthStage >= FarmTileState::MAX_GROWTH_STAGE) {
                state = HARVESTABLE;
            }
            else {
                state = GROWING;
            }
        }
    }
};


