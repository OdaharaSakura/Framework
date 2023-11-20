#pragma once
#include "component.h"
#include <string>

class GameObject;

class SphereCollider : public Component
{
private:

	class Model* m_Model{};
	GameObject* m_AttachGameObject;

	std::list<GameObject*> m_HitGameObjectlist;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	float m_Radius = 1.0f;
	float m_ScaleOffset = 100.0f;

	std::string m_HitObjectTag{};
		 
public:
	GameObject* m_testObj;

	void Init();
	void Uninit();
	void Update();
	void Draw();

	/// <summary>
	/// コライダーをつけるときは必ずこれを呼ぶ
	/// </summary>
	void SetSphireCollider(GameObject* gameobject, float radius) 
	{ 
		m_Radius = radius;
		m_AttachGameObject = gameobject;
	}

	float GetSphireColliderRadius(){ return m_Radius; }

	std::string GetHitObjectTag() { return m_HitObjectTag; }

	void AddHitGameObjectlist(GameObject* gameobject) { m_HitGameObjectlist.push_back(gameobject); }
};


