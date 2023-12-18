#pragma once

#include "component.h"
#include "main.h"

#include <list>
#include <vector>
#include <string>


class GameObject
{
protected:
	std::vector<Component*>  m_ComponentList;

	bool		m_IsActive = true;		
	bool		m_IsDestroy = false;
	bool		m_IsStatic = false;

	bool		m_IsPlayer = false;

	D3DXVECTOR3 m_WorldPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_LocalPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXMATRIX m_Matrix{};
	GameObject* m_Parent = nullptr;
	std::vector<GameObject*>	m_ChildList;

	//Shader
	bool m_IsDisplayShadow = false;
	bool m_IsEnvMapping = false;

	std::string m_Tag{};

	

public:

	virtual void Init() {}//仮想関数
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void SetDestroy(){ m_IsDestroy = true; }

	bool Destroy()
	{
		if (m_IsDestroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	void SetPosition(D3DXVECTOR3 position){ m_WorldPosition = position; }

	void SetPositionX(float positionX) { m_WorldPosition.x = positionX; }
	void SetPositionY(float positionY) { m_WorldPosition.y = positionY; }
	void SetPositionZ(float positionZ) { m_WorldPosition.z = positionZ; }


	void SetScale(D3DXVECTOR3 scale){m_Scale = scale;}
	void SetRotation(D3DXVECTOR3 rotation) { m_Rotation = rotation; }
	void SetPosScale(D3DXVECTOR3 position, D3DXVECTOR3 scale);

	void SetGameObject(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale);
	void SetDepthShadow() { m_IsDisplayShadow = true; }
	void SetEnvMapping() { m_IsEnvMapping = true; }
	void SetParent(GameObject* Parent) { m_Parent = Parent; }
	void SetPlayer() { m_IsPlayer = true; }
	

	D3DXVECTOR3 GetPosition() { return m_WorldPosition; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale() { return m_Scale; }

	D3DXVECTOR3 GetForward();//前方向ベクトル取得
	D3DXVECTOR3 GetRight();//右方向ベクトル取得
	D3DXVECTOR3 GetUp();//上方向ベクトル取得

	D3DXMATRIX GetMatrix() { return m_Matrix; }
	

	bool GetDepthShadow() { return m_IsDisplayShadow; }
	bool GetEnvMapping() { return m_IsEnvMapping; }
	bool GetPlayer() { return m_IsPlayer; }
	GameObject* GetParent() { return m_Parent; }



	template<typename T>
	T* AddComponent()
	{
		Component* component = new T();
		m_ComponentList.push_back(component);
		component->SetAttachObject(this);
		component->Init();

		return (T*)component;
	}

	template<typename T>
	void RemoveComponent()
	{
		for (auto itr = m_ComponentList.begin(); itr != m_ComponentList.end();)
		{
			if (typeid(**itr) == typeid(T))
			{
				delete* itr;
				itr = m_ComponentList.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}

	template<typename T>
	T* GetComponent()
	{
		auto itr = find_if(m_ComponentList.begin(), m_ComponentList.end(),
			[](Component* component) { return typeid(*component) == typeid(T); });

		if (itr != m_ComponentList.end())
		{
			return dynamic_cast<T*>((*itr));
		}
		else
		{
			return nullptr;
		}
	}

	template<class T>
	std::vector<T*> GetComponents()
	{
		std::vector<T*> components;
		for (Component* c : m_ComponentList)
		{
			if (typeid(*c) == typeid(T))
			{
				components.push_back(c);
			}
		}
		return components;
	}



};
