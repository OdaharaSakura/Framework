#pragma once
#include "gameObject.h"



#include <list>
#include <typeinfo>
#include <vector>


enum ObjectLayer
{
	LAYER_OBJECT_NOTDRAW,
	LAYER_CAMERA,
	LAYER_OBJECT_3D,
	LAYER_COLLIDER,
	LAYER_OBJECT_2D,
	LAYER_MAX
};

class Scene
{
protected:

	std::list<GameObject*> m_GameObject[LAYER_MAX];//レイヤーありのSTLのリスト構造//[3]ソーティングレイヤーのイメージ

public:
	virtual void Init() {}

	virtual void Uninit()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* gameObject : m_GameObject[i])//範囲forループ
			{
				gameObject->Uninit();
				delete gameObject;
			}
			m_GameObject[i].clear();//リスト構造の削除
		}

	}

	virtual void Update()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* gameObject : m_GameObject[i])//範囲forループ
			{
				gameObject->Update();
			}
			m_GameObject[i].remove_if([](GameObject* object)
				{return object->Destroy();});//ラムダ式
		}
	}

	virtual void Draw() 
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* gameObject : m_GameObject[i])//範囲forループ
			{
				gameObject->Draw();//ポリモフィズム
			}
		}
	}

	template <typename T>//テンプレート関数
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	template <typename T>//テンプレート関数
	T* GetGameObject()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//型を調べる(RTTI動的型情報)
				{
					return (T*)object;
				}
			}
		}

		return nullptr;
	}

	template <typename T>//テンプレート関数
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objects;
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//型を調べる(RTTI動的型情報)
				{
					objects.push_back((T*)object);//配列の中に入れる
				}
			}
		}
		return objects;
	}

	void DepthPath()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (auto var : m_GameObject[i])
			{
				if (var->GetDepthShadow() == true)
				{
					var->Draw();
				}
			}
		}
	}

	D3DXVECTOR3 GetPlayerPosition()
	{
		for (auto var : m_GameObject[LAYER_OBJECT_3D])
		{
			if (var->GetPlayer() == true)
			{
				return var->GetPosition();
			}
		}
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

};
