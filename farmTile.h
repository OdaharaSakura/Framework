#pragma once
#include "gameObject.h"


//�@�͂ꂽ��Ԃ�ǉ����邩�l����
enum FarmTileState
{
	EMPTY,      // ��
    PLOWED,     // �k���ꂽ
    WATERED, //����肵��
    PLANTED,    // ���A����
    PLANTED_WATERED, //���A���Đ���肵��
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


