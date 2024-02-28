#pragma once

#include "scene.h"

class Sprite;//�O���錾

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
			m_LoadingThread->join(); // �O�̃��[�f�B���O���������Ă��邱�Ƃ��m�F
		}

		m_NextScene = nextScene;
		// ���̃V�[�������[�h���邽�߂ɐV�����X���b�h���N��
		m_LoadingThread = std::make_unique<std::thread>(&Scene::Load, m_NextScene);
	}

	static bool GetIsLoadingFinish() {
		return m_LoadingThread == nullptr;
	}
};
