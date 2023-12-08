#pragma once

#include "scene.h"

class Test : public Scene
{
private:
	class Fade* m_Fade = nullptr;
	class SphereCollider* m_SphereCollider = nullptr;

	static bool m_LoadFinish;

public:
	static void Load();
	static void Unload();
	static bool GetLoadFinish() { return m_LoadFinish; }

	void Init() override;
	void Uninit() override;
	void Update() override;


};
