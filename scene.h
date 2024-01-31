#pragma once

#include "gameObject.h"

#include <list>
#include <typeinfo>
#include <vector>

class Gameobject;

enum ObjectLayer
{
	LAYER_OBJECT_NOTDRAW,
	LAYER_CAMERA,
	LAYER_OBJECT_3D,
	LAYER_COLLIDER,
	LAYER_POSTEFFECT,
	LAYER_OBJECT_2D,
	LAYER_MAX
};

enum SceneType
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_MAX
};

class Scene
{
protected:

	std::list<GameObject*> m_GameObject[LAYER_MAX];//レイヤーありのSTLのリスト構造//[3]ソーティングレイヤーのイメージ
	bool m_IsBloom = false;

public:
	virtual void Load() {}
	virtual void Unload() {}
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
				if (gameObject->GetIsStatic() == true) continue;
				if (gameObject->GetIsActive() == false) continue;
				gameObject->Update();
			}
			m_GameObject[i].remove_if([](GameObject* object)
				{return object->Destroy();});//ラムダ式
		}
	}


	void DrawCamera()
	{
		for (GameObject* gameObject : m_GameObject[LAYER_CAMERA])//範囲forループ
		{
			if (gameObject->GetIsActive() == false) continue;
			gameObject->Draw();//ポリモフィズム
		}
	}

	void Draw3DObject()
	{
		for (int i = LAYER_OBJECT_3D; i <= LAYER_COLLIDER; i++)
		{
			for (GameObject* gameObject : m_GameObject[i])//範囲forループ
			{
				if (gameObject->GetIsActive() == false) continue;
				gameObject->Draw();//ポリモフィズム
			}
		}
	}

	void Draw2DObject()
	{
		for (GameObject* gameObject : m_GameObject[LAYER_OBJECT_2D])//範囲forループ
		{
			if (gameObject->GetIsActive() == false) continue;
			gameObject->Draw();//ポリモフィズム
		}
	}


	virtual void Draw() 
	{
		DrawCamera();
		Draw3DObject();
	}

	virtual void Draw2D()
	{
		Draw2DObject();
	}


	template<typename T>
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}


	template<typename T>
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

	template<typename T>
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

	void DepthPath();
	void EnvPath();

	D3DXVECTOR3 GetEnvObjectPosition()
	{
		for (auto var : m_GameObject[LAYER_OBJECT_3D])
		{
			if (var->GetEnvMapping() == true)
			{
				return var->GetPosition();
			}
		}
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

	bool GetIsBloom() { return m_IsBloom; }

	void SetIsBloom() { m_IsBloom = true; }

};


