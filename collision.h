#pragma once
#include "gameObject.h"
#include "collider.h"
#include <vector>
#include <iterator> // std::next()�֐�����������w�b�_

class Collision
{
public:
	static std::vector<GameObject*>  m_SphereColliderObjects;//init��list��pushback
	
	static void CheckSphereCollider()
	{
		//�����������ǂ����`�F�b�N
		for (GameObject* gameobject1 : m_SphereColliderObjects)
		{
			for (GameObject* gameobject2: m_SphereColliderObjects)
			{
				if(gameobject1 != gameobject2)
				{
					//���݂���position�������A�������o��
					D3DXVECTOR3 distanceVec3 = gameobject1->GetPosition() - gameobject2->GetPosition();
					float distance = D3DXVec3Length(&distanceVec3);

					if (distance == 0) continue;

					//Radius�𑫂�
					float range =
						gameobject1->GetComponent<SphereCollider>()->GetSphireColliderRadius() +
						gameobject2->GetComponent<SphereCollider>()->GetSphireColliderRadius();

					//���� < radius�𑫂�������
					if ((distance * distance) <= (range * range))
					{
						gameobject1->GetComponent<SphereCollider>()->AddHitGameObjectlist(gameobject2);
						gameobject2->GetComponent<SphereCollider>()->AddHitGameObjectlist(gameobject1);
					}
				}
			}
		}
	}
};
