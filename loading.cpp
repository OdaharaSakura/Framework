#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "loading.h"
#include "tutorial.h"
#include "test.h"
#include "resultcamera.h"
#include "resultplayer.h"
#include "resultsky.h"
#include "loadinglogo.h"

#include "audio.h"

#include <thread>
void Loading::Init()
{

	AddGameObject<LoadingLogo>(2);

	std::thread th(&Test::Load);
	th.detach();

}
void Loading::Uninit()
{
	Scene::Uninit();
}

void Loading::Update()
{
	Scene::Update();

	if (Test::GetLoadFinish())
	{
		Manager::SetScene<Test>();
	}

}
