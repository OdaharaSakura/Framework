#pragma once

#include "scene.h"

class Sprite;//�O���錾

class Loading : public Scene
{
private:
	bool m_IsLoadingFinish = false;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
};
