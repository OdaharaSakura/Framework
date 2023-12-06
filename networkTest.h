#pragma once

#include "scene.h"

class NetWorkTest : public Scene

{
private:
	class Fade* m_Fade = nullptr;
	class SphereCollider* m_SphereCollider = nullptr;

	class Player* m_player = nullptr;
	class PlayerNetWork* m_playerNetwork = nullptr;
	class Write* m_Write = nullptr;


public:
	void Load();
	void Init() override;
	void Uninit() override;
	void Update() override;
	HRESULT Connect();

};
