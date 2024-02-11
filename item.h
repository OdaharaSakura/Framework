#pragma once
#include "GameObject.h"
#include <string>

class Item
{
private:
	std::string m_Key{};
	std::string m_TexturePass{};
	std::string m_Name{};//名前
	std::string m_Type;//アイテムの種類
	std::string m_Description{};//説明文
	int m_BuyingPrice{};//アイテムの買値
	int m_SellingPrice{};//アイテムの売値

	int m_Quantity{};//個数

public:

	Item(std::string type, std::string key, std::string texturePass,
		std::string name,  std::string description, int buyingPrice, int sellingPrice)
		: m_Type(type), m_Key(key), m_TexturePass(texturePass),
		m_Name(name),  m_Description(description), m_BuyingPrice(buyingPrice), m_SellingPrice(sellingPrice) {};
	~Item() {};

	int GetQuantity() { return m_Quantity; }
	std::string GetKey() { return m_Key; }
	std::string GetTexturePass() { return m_TexturePass; }
	std::string GetName() { return m_Name; }
	std::string GetType() { return m_Type; }
	std::string GetDescription() { return m_Description; }
	int GetBuyingPrice() { return m_BuyingPrice; }
	int GetSellingPrice() { return m_SellingPrice; }

	void SetQuantity(int quantity) { m_Quantity = quantity; }
	void SetKey(std::string key) { m_Key = key; }
	void SetTexturePass(std::string texturePass) { m_TexturePass = texturePass; }
	void SetName(std::string name) { m_Name = name; }
	void SetType(std::string type) { m_Type = type; }
	void SetDescription(std::string description) { m_Description = description; }
	void SetBuyingPrice(int buyingPrice) { m_BuyingPrice = buyingPrice; }
	void SetSellingPrice(int sellingPrice) { m_SellingPrice = sellingPrice; }

	void AddQuantity(int quantity) { m_Quantity += quantity; }
	void SubQuantity(int quantity) 
	{ 
		if (m_Quantity > 0)
		{
			m_Quantity -= quantity;
		}
		if(m_Quantity < 0)
		{
			m_Quantity = 0;
		}
	}
};
