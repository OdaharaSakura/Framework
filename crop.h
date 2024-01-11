#pragma once
#include "item.h"
#include <vector>

enum CropState {
	SEED,//í
	SEEDLING,//•c
	VEGETATIVE,//‘ä
	BUD,//‚Â‚Ú‚İ
	FLOWERING,//‰Ô
	FRUITING,//À
	MATURE,//n‚µ‚½
	DEAD//ŒÍ‚ê‚½
};

class Crop : public Item
{
private:
	int m_GrowthStage{};//¬’·’iŠK
	int m_GrowthTime{};//¬’·ŠÔ

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
