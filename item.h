#pragma once
#include "GameObject.h"
#include <string>

class Item
{
private:
	std::string m_Key{};
	std::string m_TexturePass{};
	std::string m_ModelPass{};
	std::string m_Name{};//���O
	std::string m_Type;//�A�C�e���̎��
	std::string m_Description{};//������
	int m_BuyingPrice{};//�A�C�e���̔��l
	int m_SellingPrice{};//�A�C�e���̔��l

	int m_Quantity{};//��

public:

	Item(std::string key, std::string texturePass, std::string modelPass, 
		std::string name, std::string type, std::string description, int buyingPrice, int sellingPrice)
		: m_Key(key), m_TexturePass(texturePass), m_ModelPass(modelPass),
		m_Name(name), m_Type(type), m_Description(description), m_BuyingPrice(buyingPrice), m_SellingPrice(sellingPrice) {};
	~Item() {};

	int GetQuantity() { return m_Quantity; }
	std::string GetName() { return m_Name; }
	std::string GetDescription() { return m_Description; }
	int GetBuyingPrice() { return m_BuyingPrice; }
	int GetSellingPrice() { return m_SellingPrice; }

	void SetQuantity(int quantity) { m_Quantity = quantity; }
	void SetName(std::string name) { m_Name = name; }
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
