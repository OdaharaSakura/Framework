#include "main.h"
#include "renderer.h"
#include "time.h"
#include "text.h"
#include "shader.h"
#include "observer.h"

void Time::Init()
{
	AddComponent<UnlitTexture>();
	m_Month = MonthType::Spring;
	m_Hours = 6;
	m_Minutes = 0;

	m_Start = std::chrono::system_clock::now();

	m_Text = AddComponent<Text>();
	m_TimeStr = m_MonthStr + std::to_string(m_Day) + "��\n" + std::to_string(m_Hours) + "��" + std::to_string(m_Minutes) + "��";
	m_Text->SetText(m_TimeStr);
	m_Text->SetPosition(D3DXVECTOR2(10.0f, 10.0f));
	m_Text->SetFontColor(D2D1::ColorF::White);
	m_Text->SetFontSize(40);
}

void Time::Uninit()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void Time::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();
	if (!m_IsPause)
	{
		// ���Ԍv��
		m_CountNum += std::chrono::duration<float>(std::chrono::system_clock::now() - m_Start).count();
		m_Start = std::chrono::system_clock::now();

		if (m_CountNum >= m_TimeSpeed )//5�b
		{
			m_Minutes += 10;

			m_CountNum = 0.0f;
			

			if (m_Minutes >= 60)
			{
				m_Hours += 1;
				m_Minutes = 0;
			NotifyAllObserversHour();
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
		m_MonthStr = "�͂�̌�";
		break;

	case MonthType::Summer:
		m_MonthStr = "�Ȃ̌�";
		break;

	case MonthType::Autumn:
		m_MonthStr = "�����̌�";
		break;

	case MonthType::Winter:
		m_MonthStr = "�ӂ�̌�";
		break;
	default:
		break;
	}
}

void Time::Draw()
{
	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	m_TimeStr = m_MonthStr + std::to_string(m_Day) + "��\n" + std::to_string(m_Hours) + "��" + std::to_string(m_Minutes) + "��";
	m_Text->SetText(m_TimeStr);

	//���N���X�̃��\�b�h�Ăяo��
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

void Time::NotifyAllObserversHour()
{
	for (auto observer : m_Observers)
	{
		observer->Update();
	}
}

void Time::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void Time::RemoveObserver(Observer* observer)
{
	auto it = std::remove(m_Observers.begin(), m_Observers.end(), observer);
	m_Observers.erase(it, m_Observers.end());
}



