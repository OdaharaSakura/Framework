#pragma once
#include "gameObject.h"


//�@�͂ꂽ��Ԃ�ǉ����邩�l����
enum FarmTileState
{
	EMPTY,      // ��
    PLOWED,     // �k���ꂽ
    PLOWEDWATERED, //����肵��
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


