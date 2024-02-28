#pragma once
#include "gameObject.h"

class Model;

class StaticObject : public GameObject//åpè≥
{
private:
	Model* m_Model;
	class PixelLighting* m_Shader;
	class SphereObject* sphere;

	bool m_IsBoxCollider = false;
	D3DXVECTOR3 m_BoxColliderSize;

	bool m_IsSphereCollider = false;
	float m_SphereColliderRadius;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetModel_Key(std::string model_Key);
	void SetModel_Path(std::string model_path);
	void SetModel_Null();

	bool GetIsBoxCollider() { return m_IsBoxCollider; }
	bool GetIsSphereCollider() { return m_IsSphereCollider; }
	D3DXVECTOR3 GetBoxColliderSize() { return m_BoxColliderSize; }
	float GetSphereColliderRadius() { return m_SphereColliderRadius; }

	void SetIsBoxCollider(bool isBoxCollider) { m_IsBoxCollider = isBoxCollider; }
	void SetIsBoxCollider_Size(bool isBoxCollider, D3DXVECTOR3 size ) 
	{ 
		m_IsBoxCollider = isBoxCollider; 
		m_BoxColliderSize = size;
	}
	void SetBoxColliderSize(D3DXVECTOR3 boxColliderSize) { m_BoxColliderSize = boxColliderSize; }
	void SetIsSphereCollider(bool isSphereCollider) { m_IsSphereCollider = isSphereCollider; }
	void SetIsSphereCollider_Radius(bool isSphereCollider, float radius)
	{
		m_IsSphereCollider = isSphereCollider; 
		m_SphereColliderRadius = radius;
	}
	void SetSphereColliderRadius(float sphereColliderRadius) { m_SphereColliderRadius = sphereColliderRadius; }
};
