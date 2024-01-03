#pragma once

#include "scene.h"

class Game : public Scene
{
private:
	class Fade* m_Fade = nullptr;

public:
	void Load()override;
	void Init() override;
	void Uninit() override;
	void Update() override;

	void SetEnemy();

	void SetTree();

	void SetWall();

};
