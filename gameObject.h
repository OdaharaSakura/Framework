#pragma once

#include "component.h"
#include <list>
#include <string>


class GameObject
{
protected:
	bool		m_IsDestroy = false;

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXMATRIX m_Matrix{};
	GameObject* m_Parent = nullptr;

	bool m_IsDisplayShadow = false;

	std::string m_Tag{};

	std::list<Component*>  m_Component;

public:


	void SetDestroy()
	{
		m_IsDestroy = true;
	}

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

	void SetPosScale(D3DXVECTOR3 position, D3DXVECTOR3 scale)
	{
		m_Position = position;
		m_Scale = scale;
	}

	void SetGameObject(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
	{
		m_Position = position;
		m_Rotation = rotation;
		m_Scale = scale;
	}

	D3DXVECTOR3 GetPosition() { return m_Position; }

	D3DXVECTOR3 GetRotation() { return m_Rotation; }

	D3DXVECTOR3 GetScale() { return m_Scale; }

	D3DXVECTOR3 GetForward();//前方向ベクトル取得

	D3DXVECTOR3 GetRight();//右方向ベクトル取得

	D3DXVECTOR3 GetTop();//上方向ベクトル取得

	D3DXMATRIX GetMatrix() { return m_Matrix; }

	virtual void Init() {}//仮想関数
	virtual void Uninit() 
	{
		for (Component* component : m_Component)//範囲forループ
		{
			component->Uninit();
			delete component;
		}
		m_Component.clear();//リスト構造の削除
	}
	virtual void Update() 
	{
		for (Component* component : m_Component)//範囲forループ
		{
			component->Update();
		}
	}
	virtual void Draw() 
	{
		for (Component* component : m_Component)//範囲forループ
		{
			component->Draw();//ポリモフィズム
		}
	}

	template <typename T>//テンプレート関数
	T* AddComponent()
	{
		Component* component = new T();
		m_Component.push_back(component);
		component->Init();

		return (T*)component;
	}


	template <typename T>//テンプレート関数
	T* GetComponent()
	{
		for (Component* component : m_Component)
		{
			if (typeid(*component) == typeid(T))//型を調べる(RTTI動的型情報)
			{
				return (T*)component;
			}
		}
		return nullptr;
	}

	bool GetDepthShadow()
	{
		return m_IsDisplayShadow;
	}

	void SetParent(GameObject * Parent)
	{
		m_Parent = Parent;
	}

	GameObject* GetParent(){ return m_Parent; }

};
