#include "main.h"
#include "scene.h"
#include "resultsky.h"
#include "meshField.h"
#include "Player.h"


void Scene::DepthPath()
{
	for (int i = 0; i < LAYER_MAX; i++)
	{
		for (auto var : m_GameObject[LAYER_OBJECT_3D])
		{
			if (var->GetDepthShadow() == true)
			{
				var->Draw();
			}
		}
	}
}

void Scene::EnvPath()
{
	GetGameObject<ResultSky>()->Draw();
	GetGameObject<MeshField>()->Draw();
	GetGameObject<Player>()->Draw();
}


