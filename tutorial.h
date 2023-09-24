#pragma once

#include "scene.h"

class Tutorial : public Scene
{
private:
	class Fade* m_Fade = nullptr;

public:
	void Init() override;
	void Update() override;
};