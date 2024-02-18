#pragma once

#include "gameObject.h"
#include <string>

class Text;
class InventoryItemDescription : public GameObject
{
private:
	static const int m_textObjNum = 4;

	GameObject* m_ItemText[m_textObjNum];//テキストの数のオブジェクト生成

	Text* m_ItemNameText;
	Text* m_ItemTypeText;
	Text* m_ItemDescriptionText;
	Text* m_ItemQuantityText;

	class Inventory* m_Inventory;
	class InventoryItemCursor* m_InventoryItemCursor;

	int m_Index{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetText(Text* textptr, const std::string& text);
};
