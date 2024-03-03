#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "loading.h"
#include "tutorial.h"
#include "game.h"
#include "resultcamera.h"
#include "resultplayer.h"
#include "resultsky.h"
#include "loadinglogo.h"

#include "audio.h"

#include <thread>
void Loading::Init()
{

	AddGameObject<LoadingLogo>(LAYER_OBJECT_2D);

	std::thread th(&Game::Load);
	th.detach();

}
void Loading::Uninit()
{
	Scene::Uninit();
}

void Loading::Update()
{
	Scene::Update();

	if (Game::GetLoadFinish())
	{
		Manager::SetScene<Game>();
	}

}
