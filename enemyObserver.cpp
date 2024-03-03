#include "enemyObserver.h"
#include "time.h"
#include "scene.h"
#include "manager.h"
#include "enemy.h"

EnemyObserver::EnemyObserver()
{
	Scene* scene = Manager::GetScene();
	Time* time = scene->GetGameObject<Time>();
	time->AddObserver(this);
}

EnemyObserver::~EnemyObserver()
{
	Scene* scene = Manager::GetScene();
	Time* time = scene->GetGameObject<Time>();
	if (time != nullptr)time->RemoveObserver(this);
}

void EnemyObserver::UpdateHour()
{

	Scene* scene = Manager::GetScene();

	Enemy* enemy = scene->GetGameObject<Enemy>();
	if (enemy == nullptr)
	{
		m_Hour++;
	}
	if (m_Hour >= 4)
	{
		m_Hour = 0;
		scene->AddGameObject<Enemy>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(0.0f, 1.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	}
}

void EnemyObserver::SetIncrementTime(int minute, int hour, int day)
{
	m_Minute += minute;
	m_Hour += (hour + (minute / 60) + (day * 24));

	Scene* scene = Manager::GetScene();

	Enemy* enemy = scene->GetGameObject<Enemy>();
	if (enemy == nullptr)
	{
		return;
	}

	if (m_Hour >= 4)
	{
		m_Hour = 0;
		scene->AddGameObject<Enemy>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(0.0f, 1.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	}

}

