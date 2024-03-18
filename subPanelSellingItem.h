#pragma once
#include "GameObject.h"

#include <string>
#include <map>

class SubPanelSellingItem :public GameObject
{
private:
	class StaticSprite* m_StaticSprite{};
	class Text* m_Text{};
	int m_SellingItemQuantity{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	
	void SellingItem(int quantity, class Item* itemPtr);

	void SetSellingItemQuantity(int quantity) { m_SellingItemQuantity = quantity; }
};