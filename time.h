#pragma once
#include "gameObject.h"
#include "savedata.h"

#include <iostream>
#include <string>
#include <chrono>

enum MonthType
{
	Spring,
	Summer,
	Autumn,
	Winter
};


class Time : public GameObject
{
private:
	std::chrono::time_point<std::chrono::system_clock> m_Start{};
	std::chrono::time_point<std::chrono::system_clock> m_Now{};
	class Text* m_Text = nullptr;
	std::string m_MonthStr;
	std::string m_TimeStr;

	int m_Month = MonthType::Spring;
	int m_Day = 1;
	int m_Hours = 6;
	int m_Minutes{};

	int m_IncrementDay{};
	int m_IncrementHour{};
	int m_IncrementMinute{};

	float m_CountNum = 0.0f;
	float m_OneSecondCount = 1.0f;
	float m_RealTimeSpeed = 1.0f;

	bool m_IsPause = false;

	std::vector<class TimeObserver*> m_Observers;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Pause() { m_IsPause = true; }
	void Resume() 
	{ 
		m_IsPause = false; 
		m_Start = std::chrono::system_clock::now();
	}

	// 時間の進行を停止した後計測するために、start変数を更新する
	void SetStartTime() {m_Start = std::chrono::system_clock::now();}
	void SetSleep();//眠る

	int GetMonth() { return m_Month; }
	int GetDay() { return m_Day; }
	int GetHours() { return m_Hours; }
	int GetMinutes() { return m_Minutes; }

	int GetIncrementDay() { return m_IncrementDay; }
	int GetIncrementHour() { return m_IncrementHour; }
	int GetIncrementMinute() { return m_IncrementMinute; }

	void NotifyAllTimeObservers();
	void NotifyAllTimeObserversHour();
	void NotifyAllTimeObserversMinute();
	void AddObserver(class TimeObserver* observer);
	void RemoveObserver(class TimeObserver* observer);

	void ClearObserver();

	void Load(TimeData timedata);
};
