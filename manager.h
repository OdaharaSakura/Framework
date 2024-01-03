#pragma once
#include "scene.h"
#include "renderer.h"

enum SceneType
{
	TitleScene,
	GameScene,
	ResultScene,
	LoadingScene,
	TestScene
};

class Manager
{
private:
	static Scene* m_Scene;
	static Scene* m_NextScene;

	static Renderer* m_Renderer;
	static bool m_IsGameFinish;
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void LightInitialize(LIGHT* light, D3DXVECTOR3 position);

	static Scene* GetScene() { return m_Scene; }
	static Scene* GetNextScene() { return m_NextScene; }
	static Renderer* GetRenderer() { return m_Renderer; }

	template <typename T>//テンプレート関数
	static void SetScene()
	{
		m_NextScene = new T();
	}

	static void SetIsGameFinish() { m_IsGameFinish = true; }
	static bool GetIsGameFinish() { return m_IsGameFinish; }
};