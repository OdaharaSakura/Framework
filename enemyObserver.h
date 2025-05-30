#pragma once
#include "timeObserver.h"
class EnemyObserver : public TimeObserver
{
private:

	int m_Hour{};
	int m_Minute{};
public:
	EnemyObserver();
	~EnemyObserver();

	void UpdateMinute() {}
	void UpdateHour();
	void UpdateDay() {}
	void SetIncrementTime(int minute, int hour, int day);

	int GetMinute() { return m_Minute; }

	void SetMinute(int minute) { m_Minute = minute; }
};
