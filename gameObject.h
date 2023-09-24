#pragma once

#include "component.h"
#include <list>

class GameObject
{
protected:
	bool		m_Destroy = false;

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXMATRIX m_Matrix{};


	std::list<Component*>  m_Component;

public:


	void SetDestroy()
	{
		m_Destroy = true;
	}

	bool Destroy()
	{
		if (m_Destroy)
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



	void SetPosition(D3DXVECTOR3 position){m_Position = position;}

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

	D3DXVECTOR3 GetPosition()
	{
		return m_Position;
	}

	D3DXVECTOR3 GetScale()
	{
		return m_Scale;
	}

	D3DXVECTOR3 GetForward()//前方向ベクトル取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight()//右方向ベクトル取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}


	D3DXVECTOR3 GetTop()//上方向ベクトル取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXVECTOR3 top;
		top.x = rot._21;
		top.y = rot._22;
		top.z = rot._23;

		return top;
	}

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
};
