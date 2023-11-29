#pragma once

#include "component.h"

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

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXMATRIX m_Matrix{};
	GameObject* m_Parent = nullptr;
	std::vector<GameObject*>	m_ChildList;

	bool m_IsDisplayShadow = false;

	std::string m_Tag{};

	

public:


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

	void SetPosition(D3DXVECTOR3 position){ m_Position = position; }

	void SetPositionX(float positionX) { m_Position.x = positionX; }
	void SetPositionY(float positionY) { m_Position.y = positionY; }
	void SetPositionZ(float positionZ) { m_Position.z = positionZ; }


	void SetScale(D3DXVECTOR3 scale){m_Scale = scale;}
	void SetRotation(D3DXVECTOR3 rotation) { m_Rotation = rotation; }
	void SetPosScale(D3DXVECTOR3 position, D3DXVECTOR3 scale);

	void SetGameObject(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale);

	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale() { return m_Scale; }

	D3DXVECTOR3 GetForward();//前方向ベクトル取得
	D3DXVECTOR3 GetRight();//右方向ベクトル取得
	D3DXVECTOR3 GetTop();//上方向ベクトル取得

	D3DXMATRIX GetMatrix() { return m_Matrix; }
	void SetParent(GameObject* Parent) { m_Parent = Parent; }

	bool GetDepthShadow() { return m_IsDisplayShadow; }
	GameObject* GetParent() { return m_Parent; }

	virtual void Init() {}//仮想関数
	virtual void Uninit() 
	{
		for (Component* component : m_ComponentList)//範囲forループ
		{
			component->Uninit();
			delete component;
		}
		m_ComponentList.clear();//リスト構造の削除
	}
	virtual void Update() 
	{
		for (Component* component : m_ComponentList)//範囲forループ
		{
			component->Update();
		}
	}
	virtual void Draw() 
	{
		for (Component* component : m_ComponentList)//範囲forループ
		{
			component->Draw();//ポリモフィズム
		}
	}

	template<typename T>
	T* AddComponent()
	{
		Component* component = new T();
		m_ComponentList.push_back(component);
		component->Init();

		return (T*)component;
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
