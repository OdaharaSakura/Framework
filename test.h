#pragma once

#include "scene.h"

class Test : public Scene
{
private:
	class Fade* m_Fade = nullptr;
	class SphereCollider* m_SphereCollider = nullptr;

	

public:
	void Load();
	void Init() override;
	void Uninit() override;
	void Update() override;


};
