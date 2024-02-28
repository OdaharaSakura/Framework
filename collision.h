//#pragma once
//#include "gameObject.h"
//#include "collider.h"
//#include <vector>
//#include <iterator> // std::next()�֐�����������w�b�_
//
//class Collision
//{
//public:
//
//	
//	static void CheckSphereCollider()
//	{
//		//�����������ǂ����`�F�b�N
//		for (GameObject* gameobject1 : m_SphereColliderObjects)
//		{
//			for (GameObject* gameobject2: m_SphereColliderObjects)
//			{
//				if(gameobject1 != gameobject2)
//				{
//					//���݂���position�������A�������o��
//					D3DXVECTOR3 distanceVec3 = gameobject1->GetPosition() - gameobject2->GetPosition();
//					float distance = D3DXVec3Length(&distanceVec3);
//
//
//					//Radius�𑫂�
//					float range =
//						gameobject1->GetComponent<SphereCollider>()->GetSphireColliderRadius() +
//						gameobject2->GetComponent<SphereCollider>()->GetSphireColliderRadius();
//
//					//���� < radius�𑫂�������
//					if ((distance * distance) <= (range * range))
//					{//�������Ă���
//						gameobject1->GetComponent<SphereCollider>()->AddHitGameObjectlist(gameobject2);
//						gameobject2->GetComponent<SphereCollider>()->AddHitGameObjectlist(gameobject1);
//					}
//					else
//					{
//						auto gameobject1itr = std::find(gameobject1->GetComponent<SphereCollider>()->GetHitGameObjectlist().begin(),  gameobject1->GetComponent<SphereCollider>()->GetHitGameObjectlist().end(), gameobject1);
//						if (gameobject1itr != gameobject1->GetComponent<SphereCollider>()->GetHitGameObjectlist().end()) {
//							m_SphereColliderObjects.erase(gameobject1itr);
//						}
//
//						auto gameobject2itr = std::find(gameobject2->GetComponent<SphereCollider>()->GetHitGameObjectlist().begin(), gameobject2->GetComponent<SphereCollider>()->GetHitGameObjectlist().end(), gameobject2);
//						if (gameobject2itr != gameobject2->GetComponent<SphereCollider>()->GetHitGameObjectlist().end()) {
//							m_SphereColliderObjects.erase(gameobject2itr);
//						}
//					}
//				}
//			}
//		}
//	}
//};
