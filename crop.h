#pragma once
#include "item.h"
#include <vector>

enum CropState {
	SEED,//��
	SEEDLING,//�c
	VEGETATIVE,//����
	BUD,//�ڂ�
	FLOWERING,//��
	FRUITING,//��
	MATURE,//�n����
	DEAD//�͂ꂽ
};

class Crop : public Item
{
private:
	int m_GrowthStage{};//�����i�K
	int m_GrowthTime{};//��������

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

class Tomato : public Crop
{
private:

public:
	Tomato();
	~Tomato();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
