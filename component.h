#pragma once

class Component
{
protected:
	
	class GameObject* m_AttachObject;
	bool		m_IsActive = true;					// �A�N�e�B�u�t���O
	bool		m_IsDestroy = false;				// �폜�t���O

public:
	virtual void Init() {}//���z�֐�
	virtual void Uninit() {}
	virtual void Update() {}
	virtual void Draw() {}

	// ���g�̍폜��\��
	virtual void SetDestroy() { m_IsDestroy = true; }
	// �폜����
	void Destroy();

	void SetAttachObject(GameObject* gameobject) { m_AttachObject = gameobject; }
};
