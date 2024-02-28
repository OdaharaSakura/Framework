//#pragma once
//#include "gameObject.h"
//#include "collider.h"
//#include <vector>
//#include <iterator> // std::next()関数が所属するヘッダ
//
//class Collision
//{
//public:
//
//	
//	static void CheckSphereCollider()
//	{
//		//当たったかどうかチェック
//		for (GameObject* gameobject1 : m_SphereColliderObjects)
//		{
//			for (GameObject* gameobject2: m_SphereColliderObjects)
//			{
//				if(gameobject1 != gameobject2)
//				{
//					//お互いのpositionを引き、距離を出す
//					D3DXVECTOR3 distanceVec3 = gameobject1->GetPosition() - gameobject2->GetPosition();
//					float distance = D3DXVec3Length(&distanceVec3);
//
//
//					//Radiusを足す
//					float range =
//						gameobject1->GetComponent<SphereCollider>()->GetSphireColliderRadius() +
//						gameobject2->GetComponent<SphereCollider>()->GetSphireColliderRadius();
//
//					//距離 < radiusを足したもの
//					if ((distance * distance) <= (range * range))
//					{//当たっている
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
