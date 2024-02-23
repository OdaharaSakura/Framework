#pragma once

class TimeObserver
{
private:
	int m_RealSeconds{};//設定はTimeクラスで行うのでコンストラクタで呼び出すこと
		
public:

	TimeObserver(){};

	~TimeObserver(){};

	virtual void UpdateHour() = 0;

	void SetRealOneSecond()//ココ微妙
	{
		m_RealSeconds++;
	}
};