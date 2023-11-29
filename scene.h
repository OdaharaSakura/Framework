#pragma once
#include "gameObject.h"
#include "collision.h"

#include <list>
#include <typeinfo>
#include <vector>


enum ObjectLayer
{
	CAMERA_LAYER,
	OBJECT_3D_LAYER,
	COLLIDER_LAYER,
	OBJECT_2D_LAYER,
	MAX_LAYER
};

class Scene
{
protected:

	std::list<GameObject*> m_GameObject[MAX_LAYER];//���C���[�����STL�̃��X�g�\��//[3]�\�[�e�B���O���C���[�̃C���[�W

public:
	virtual void Init() {}

	virtual void Uninit()
	{
		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (GameObject* gameObject : m_GameObject[i])//�͈�for���[�v
			{
				gameObject->Uninit();
				delete gameObject;
			}
			m_GameObject[i].clear();//���X�g�\���̍폜
		}

	}

	virtual void Update()
	{
		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (GameObject* gameObject : m_GameObject[i])//�͈�for���[�v
			{
				gameObject->Update();
			}
			m_GameObject[i].remove_if([](GameObject* object)
				{return object->Destroy();});//�����_��
		}

		//Collision::CheckSphereCollider();
	}

	virtual void Draw() 
	{
		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (GameObject* gameObject : m_GameObject[i])//�͈�for���[�v
			{
				gameObject->Draw();//�|�����t�B�Y��
			}
		}
	}

	template <typename T>//�e���v���[�g�֐�
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	template <typename T>//�e���v���[�g�֐�
	T* GetGameObject()
	{
		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//�^�𒲂ׂ�(RTTI���I�^���)
				{
					return (T*)object;
				}
			}
		}

		return nullptr;
	}

	template <typename T>//�e���v���[�g�֐�
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objects;
		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//�^�𒲂ׂ�(RTTI���I�^���)
				{
					objects.push_back((T*)object);//�z��̒��ɓ����
				}
			}
		}
		return objects;
	}

	void DepthPath()
	{
		for (int i = 0; i < MAX_LAYER; i++)
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

};
