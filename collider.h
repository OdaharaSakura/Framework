#pragma once
#include "component.h"
#include <string>
#include <vector>

class GameObject;
class SphereObject;

class SphereCollider : public Component
{
private:

	class Model* m_Model{};

	std::vector<GameObject*> m_HitGameObjectlist;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXVECTOR3 m_WorldPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	float m_Radius = 1.0f;
	float m_ScaleOffset = 1.0f;

	std::string m_HitObjectTag{};
		 
public:
	SphereObject* m_SphereObj;

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetSphereCollider(float radius, D3DXVECTOR3 position) 
	{ 
		m_Radius = radius;
		m_WorldPosition = position;
	}

	float GetSphireColliderRadius(){ return m_Radius; }

	std::string GetHitObjectTag() { return m_HitObjectTag; }

	void AddHitGameObjectlist(GameObject* gameobject) { m_HitGameObjectlist.push_back(gameobject); }
	std::vector<GameObject*> GetHitGameObjectlist() { return m_HitGameObjectlist; }
};


