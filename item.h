#pragma once

#include <string>

class Item
{
protected:
	std::string m_Key{};
	std::string m_TexturePass{};
	std::string m_Name{};//���O
	std::string m_Type;//�A�C�e���̎��
	std::string m_Description{};//������
	int m_BuyingPrice{};//�A�C�e���̔��l
	int m_SellingPrice{};//�A�C�e���̔��l
	bool m_IsEat{};
	int m_Healing{};

	int m_Quantity = 1;//��

public:

	Item(std::string type, std::string key, std::string texturePass,
		std::string name,  std::string description, int buyingPrice, int sellingPrice, bool isEat, int healing)
		: m_Type(type), m_Key(key), m_TexturePass(texturePass),
		m_Name(name),  m_Description(description), m_BuyingPrice(buyingPrice), m_SellingPrice(sellingPrice), m_IsEat(isEat), m_Healing(healing){};
	~Item() {};

	int GetQuantity() { return m_Quantity; }
	std::string GetKey() { return m_Key; }
	std::string GetTexturePass() { return m_TexturePass; }
	std::string GetName() { return m_Name; }
	std::string GetType() { return m_Type; }
	std::string GetDescription() { return m_Description; }
	int GetBuyingPrice() { return m_BuyingPrice; }
	int GetSellingPrice() { return m_SellingPrice; }
	bool GetIsEat() { return m_IsEat; }
	int GetHealing() { return m_Healing; }

	void AddQuantity(int quantity) { m_Quantity += quantity; }
	void SubQuantity(int quantity) 
	{ 
		if (m_Quantity > 0)
		{
			m_Quantity -= quantity;
		}
		if(m_Quantity <= 0)
		{
			m_Quantity = 0;
		}
	}
};
