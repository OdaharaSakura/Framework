#pragma once
#include "gameObject.h"
#include "collider.h"
#include <vector>
#include <iterator> // std::next()関数が所属するヘッダ

class Collision
{
public:
	static std::vector<GameObject*>  m_SphereColliderObjects;//initでlistにpushback
	
	static void CheckSphereCollider()
	{
		//当たったかどうかチェック
		for (GameObject* gameobject1 : m_SphereColliderObjects)
		{
			for (GameObject* gameobject2: m_SphereColliderObjects)
			{
				if(gameobject1 != gameobject2)
				{
					//お互いのpositionを引き、距離を出す
					D3DXVECTOR3 distanceVec3 = gameobject1->GetPosition() - gameobject2->GetPosition();
					float distance = D3DXVec3Length(&distanceVec3);

					if (distance == 0) continue;

					//Radiusを足す
					float range =
						gameobject1->GetComponent<SphereCollider>()->GetSphireColliderRadius() +
						gameobject2->GetComponent<SphereCollider>()->GetSphireColliderRadius();

					//距離 < radiusを足したもの
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
