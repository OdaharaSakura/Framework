#pragma once

class Component
{
protected:
	
	class GameObject* m_AttachObject;
	bool 		m_IsStatic = false;					// 初期化フラグ	
	bool		m_IsActive = true;					// アクティブフラグ
	bool		m_IsEnable = true;					// 有効フラグ
	bool		m_IsDestroy = false;				// 削除フラグ

public:
	virtual void Init() {}//仮想関数
	virtual void Uninit() {}
	virtual void Update() {}
	virtual void Draw() {}

	// 自身の削除を予約
	virtual void SetDestroy() { m_IsDestroy = true; }

	// 削除処理
	void Destroy();


	void SetAttachObject(GameObject* gameobject) { m_AttachObject = gameobject; }
	void SetIsActive(bool isActive) { m_IsActive = isActive; }
	void SetIsStatic(bool isStatic) { m_IsStatic = isStatic; }
	void SetIsEnable(bool isEnable) { m_IsEnable = isEnable; }

	bool GetIsActive() { return m_IsActive; }
	bool GetIsStatic() { return m_IsStatic; }
	bool GetIsEnable() { return m_IsEnable; }
};
