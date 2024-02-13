#pragma once
#include "item.h"
#include <vector>

class Equipment : public Item
{
protected:
	std::string m_ModelPass{};
	int m_LostHP{};

	class Player* m_Player{};
public:
	Equipment(std::string type, std::string key, std::string texturePass,
		std::string name, std::string description, int buyingPrice, int sellingPrice,
		std::string modelPass, int lostHP)
		: Item(type, key, texturePass, name, description, buyingPrice, sellingPrice),
		m_ModelPass(modelPass), m_LostHP(lostHP){};
	~Equipment() {};

	void Init() {};
	virtual void Execute() {};

	std::string GetModelPass() { return m_ModelPass; }
};

//ŒL
#pragma region Hoe 
class Hoe : public Equipment
{
public:

	Hoe(std::string type, std::string key, std::string texturePass,
		std::string name, std::string description, int buyingPrice, int sellingPrice,
		std::string modelPass, int lostHP)
		: Equipment(type, key, texturePass, name, description, buyingPrice, sellingPrice, modelPass, lostHP)
	{}
	void Init() {};
	void Execute() override;
};
#pragma endregion

//Š™
#pragma region Sickle 
class Sickle : public Equipment
{
public:

	Sickle(std::string type, std::string key, std::string texturePass,
		std::string name, std::string description, int buyingPrice, int sellingPrice,
		std::string modelPass, int lostHP)
		: Equipment(type, key, texturePass, name, description, buyingPrice, sellingPrice, modelPass, lostHP)
	{}
	void Init() {};
	void Execute() override;
};
#pragma endregion

