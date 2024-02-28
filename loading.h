#pragma once

#include "scene.h"

class Sprite;//前方宣言

class Loading : public Scene
{
private:
	bool m_IsLoadingFinish = false;
	static std::unique_ptr<std::thread> m_LoadingThread;
	static Scene* m_NextScene;
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	static void SetNextScene(Scene* nextScene) {
		if (m_LoadingThread && m_LoadingThread->joinable()) {
			m_LoadingThread->join(); // 前のローディングが完了していることを確認
		}

		m_NextScene = nextScene;
		// 次のシーンをロードするために新しいスレッドを起動
		m_LoadingThread = std::make_unique<std::thread>(&Scene::Load, m_NextScene);
	}

	static bool GetIsLoadingFinish() {
		return m_LoadingThread == nullptr;
	}
};
