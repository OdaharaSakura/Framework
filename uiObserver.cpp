#include "uiObserver.h"
#include "time.h"
#include "scene.h"
#include "manager.h"
#include "polygon2D.h"
#include "sceneDescription.h"

UIObserver::UIObserver()
{
	Scene* scene = Manager::GetScene();
	Time* time = scene->GetGameObject<Time>();
	time->AddObserver(this);
}

UIObserver::~UIObserver()
{
	Scene* scene = Manager::GetScene();
	Time* time = scene->GetGameObject<Time>();
	if (time != nullptr)time->RemoveObserver(this);
}

void UIObserver::UpdateMinute()
{
	Scene* scene = Manager::GetScene();
	Polygon2D* polygon2D = scene->GetGameObject<Polygon2D>();
	SceneDescription* sceneDescription = scene->GetGameObject<SceneDescription>();

	sceneDescription->SetDescriptionText("");

	m_Minute += 10; // •ª‚ð‰ÁŽZ
	if (m_Minute >= 60 && !polygon2D->GetIsChangeUI())
	{
		m_Minute = 0; // 0•ª‚É–ß‚·
		polygon2D->SetIsChangeUI(true);
	}
}


