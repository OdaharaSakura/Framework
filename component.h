#pragma once

class Component
{
protected:
	
	class GameObject* m_AttachObject;
	bool		m_IsActive = true;					// アクティブフラグ
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
};
