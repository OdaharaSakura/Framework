#pragma once
#include "GameObject.h"
#include <string>

class Item : public GameObject
{
private:
	int m_Quantity{};//��
	std::string m_Name{};//���O
	std::string m_Description{};//������
	int m_BuyingPrice{};//�A�C�e���̔��l
	int m_SellingPrice{};//�A�C�e���̔��l

public:
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
