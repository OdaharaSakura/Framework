#include "main.h"
#include "renderer.h"
#include "time.h"
#include "text.h"
#include "shader.h"

void Time::Init()
{
	AddComponent<UnlitTexture>();
	m_Month = MonthType::Spring;
	m_Hours = 6;
	m_Minutes = 0;

	m_Start = std::chrono::system_clock::now();

	m_Text = AddComponent<Text>();
	m_TimeStr = m_MonthStr + std::to_string(m_Day) + "日\n" + std::to_string(m_Hours) + "時" + std::to_string(m_Minutes) + "分";
	m_Text->Init(m_TimeStr,
		D3DXVECTOR2(10.0f, 10.0f),
		DWRITE_FONT_WEIGHT_LIGHT,
		D2D1::ColorF::AliceBlue,
		Font_NicocaV2);
	m_Text->SetFontSize(40);
}

void Time::Uninit()
{
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
		m_CountNum += std::chrono::duration<float>(std::chrono::system_clock::now() - m_Start).count();
		m_Start = std::chrono::system_clock::now();

		if (m_CountNum >= m_TimeSpeed )//5秒
		{
			m_Minutes += 10;

			m_CountNum = 0.0f;
			

			if (m_Minutes >= 60)
			{
				m_Hours += 1;
				m_Minutes = 0;
			}
			if (m_Hours >= 24)
			{
				m_Hours = 0;
				m_Day += 1;
			}
			if (m_Day >= 31)
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



