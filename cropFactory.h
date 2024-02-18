#pragma once
#include "crop.h"

class CropFactory
{
public:
	CropFactory() {};
	~CropFactory() {};



	Crop* CreateCrop(std::string key);
};