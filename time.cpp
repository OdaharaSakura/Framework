#include "main.h"
#include "renderer.h"
#include "time.h"
#include "text.h"
#include "shader.h"
#include "timeObserver.h"

void Time::Init()
{
	AddComponent<UnlitTexture>();
	m_Month = MonthType::Spring;
	m_Hours = 6;
	m_Minutes = 0;

	m_Start = std::chrono::system_clock::now();
	m_Now = std::chrono::system_clock::now();

	m_Text = AddComponent<Text>();
	m_TimeStr = m_MonthStr + std::to_string(m_Day) + "日\n" + std::to_string(m_Hours) + "時" + std::to_string(m_Minutes) + "分";
	m_Text->SetText(m_TimeStr);
	m_Text->SetPosition(D3DXVECTOR2(10.0f, 10.0f));
	m_Text->SetFontColor(D2D1::ColorF::White);
	m_Text->SetFontSize(40);
}

void Time::Uninit()
{
	//ClearObserver();
	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void Time::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();
	if (!m_IsPause)
	{
		// 時間計測
		m_CountNum += std::chrono::duration<float>(std::chrono::system_clock::now() - m_Now).count();
		m_Now = std::chrono::system_clock::now();

		if (m_OneSecondCount >= 1)
		{
			NotifyAllTimeObservers();
			m_OneSecondCount = 0.0f;
		}


		if (m_CountNum >= m_RealTimeSpeed )
		{
			m_Minutes += 10;
			NotifyAllTimeObserversMinute();

			m_CountNum = 0.0f;
			

			if (m_Minutes >= 60)
			{
				m_Hours += 1;
				m_Minutes = 0;
			NotifyAllTimeObserversHour();
			}
			if (m_Hours >= 24)
			{
				m_Hours = 0;
				m_Day += 1;
			}
			
			int monthDays = 31;
			if (m_Day >= monthDays)
			{
				m_Day = 1;

				if (m_Month == MonthType::Winter)
				{
					m_Month = MonthType::Spring;
				}
				else
				{
					m_Month += 1;
				}
			}
		}
		
	}
	
	switch (m_Month)
	{
	case MonthType::Spring:
		m_MonthStr = "はるの月";
		break;

	case MonthType::Summer:
		m_MonthStr = "なつの月";
		break;

	case MonthType::Autumn:
		m_MonthStr = "あきの月";
		break;

	case MonthType::Winter:
		m_MonthStr = "ふゆの月";
		break;
	default:
		break;
	}
}

void Time::Draw()
{
	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	m_TimeStr = m_MonthStr + std::to_string(m_Day) + "日\n" + std::to_string(m_Hours) + "時" + std::to_string(m_Minutes) + "分";
	m_Text->SetText(m_TimeStr);

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}

void Time::SetSleep()
{
	m_Hours = 6;
	m_Minutes = 0;

	if (m_Hours <= 24 && m_Hours >= 6)
	{
		m_Day += 1;
	}
}

void Time::NotifyAllTimeObservers()
{
	for (auto observer : m_Observers)
	{
		//TODO:observerによって計測するかどうか考えたほうが良い
		observer->SetRealOneSecond();
	}
}

void Time::NotifyAllTimeObserversHour()
{
	for (auto observer : m_Observers)
	{
		observer->UpdateHour();
	}
}

void Time::NotifyAllTimeObserversMinute()
{
	for (auto observer : m_Observers)
	{
		observer->UpdateMinute();
	}
}

void Time::AddObserver(TimeObserver* observer)
{
	m_Observers.push_back(observer);
}

void Time::RemoveObserver(TimeObserver* observer)
{
	auto it = std::remove(m_Observers.begin(), m_Observers.end(), observer);
	m_Observers.erase(it, m_Observers.end());
}

void Time::ClearObserver()
{
    //全てのオブザーバーを削除
    m_Observers.clear();
}

void Time::Load(TimeData timedata)
{
	m_Month = timedata.month;
	m_Day = timedata.day;
	m_Hours = timedata.hour;
	m_Minutes = timedata.minute;
}



