#pragma once

class Component
{
protected:
	
	class GameObject* m_AttachObject;
	bool 		m_IsStatic = false;					// �������t���O	
	bool		m_IsActive = true;					// �A�N�e�B�u�t���O
	bool		m_IsEnable = true;					// �L���t���O
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
	void SetIsActive(bool isActive) { m_IsActive = isActive; }
	void SetIsStatic(bool isStatic) { m_IsStatic = isStatic; }
	void SetIsEnable(bool isEnable) { m_IsEnable = isEnable; }

	bool GetIsActive() { return m_IsActive; }
	bool GetIsStatic() { return m_IsStatic; }
	bool GetIsEnable() { return m_IsEnable; }
};
