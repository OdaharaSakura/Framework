#pragma once



class Component
{
protected:
	
	//class GameObject* m_GameObject;


public:
	virtual void Init() {}//âºëzä÷êî
	virtual void Uninit() {}
	virtual void Update() {}
	virtual void Draw() {}
};
