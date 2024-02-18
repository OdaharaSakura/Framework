#pragma once
#include "gameObject.h"
#include "crop.h"

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


