#pragma once
#include "timeObserver.h"
class CropObserver : public TimeObserver
{
private:
		class Crop* m_Crop;
		class FarmTile* m_FarmTile;

		int m_Hour{};
		int m_Minute{};
public:
	CropObserver(class FarmTile* farmTile ,class Crop* crop);
	~CropObserver();

	void UpdateMinute();
	void UpdateHour() {}
	void UpdateDay() {}

	int GetMinute() { return m_Minute; }

	void SetMinute(int minute) { m_Minute = minute; }
};
