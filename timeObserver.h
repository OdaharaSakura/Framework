#pragma once

class TimeObserver
{
private:
	int m_RealSeconds{};//�ݒ��Time�N���X�ōs���̂ŃR���X�g���N�^�ŌĂяo������
		
public:

	TimeObserver(){};

	~TimeObserver(){};

	virtual void UpdateDay() = 0;
	virtual void UpdateHour() = 0;
	virtual void UpdateMinute() = 0;

	void SetRealOneSecond()//�R�R����
	{
		m_RealSeconds++;
	}
};