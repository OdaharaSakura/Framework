#pragma once
#include "timeObserver.h"
class UIObserver : public TimeObserver
{
private:

	int m_Hour{};
	int m_Minute{};
public:
	UIObserver();
	~UIObserver();

	void UpdateMinute();
	void UpdateHour() {}
	void UpdateDay() {}
	void SetIncrementTime(int minute, int hour, int day) {}

	int GetMinute() { return m_Minute; }

	void SetMinute(int minute) { m_Minute = minute; }
};
