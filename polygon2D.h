#pragma once

#include "gameObject.h"
#include <string>

enum UIType
{
	UIType_TIPS_WASD,
	UIType_TIPS_SPACE,
	UIType_TIPS_E,
	UIType_TIPS_TAB,
	UIType_TIPS_UO,
	UIType_TIPS_MAX
};

class Polygon2D : public GameObject
{
private:
	class StaticSprite* m_TIPS{};

	//UIÇêÿÇËë÷Ç¶ÇÈ
	bool m_IsChangeUI = false;

	std::string key[UIType_TIPS_MAX]{};
	std::string path[UIType_TIPS_MAX]{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetIsChangeUI(bool isChangeUI) { m_IsChangeUI = isChangeUI; }
	bool GetIsChangeUI() { return m_IsChangeUI; }
};
