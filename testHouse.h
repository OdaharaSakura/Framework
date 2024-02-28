#pragma once

#include "scene.h"

class TestHouse : public Scene
{
private:
	class Fade* m_Fade = nullptr;

public:
	void Load()override;
	void Unload()override;

	void Init() override;
	void Uninit() override;
	void Update() override;


};
