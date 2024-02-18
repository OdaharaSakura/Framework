#pragma once
#include "observer.h"
class CropObserver : public Observer
{
private:
		class Crop* m_Crop;
		class FarmTile* m_FarmTile;

		int m_Hour{};
public:
	CropObserver(class FarmTile* farmTile ,class Crop* crop);
	~CropObserver();

	void Update();

};
