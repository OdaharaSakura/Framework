#pragma once
#include "item.h"
#include <vector>

class Equipment
{
protected:
	std::string m_Key{};
	std::string m_TexturePass{};
	std::string m_ModelPass{};
	int m_LostHP{};

	class Player* m_Player{};
public:
	Equipment(std::string key, std::string texturePass,
		std::string modelPass, int lostHP)
		: m_Key(key), m_TexturePass(texturePass),
		m_ModelPass(modelPass), m_LostHP(lostHP){};
	~Equipment() {};

	virtual void Execute() {};

	std::string GetKey() { return m_Key; }
	std::string GetTexturePass() { return m_TexturePass; }
	std::string GetModelPass() { return m_ModelPass; }
	int GetLostHp() { return m_LostHP; }
};

//ŒL
#pragma region Hoe 
class Hoe : public Equipment
{
public:

	Hoe(std::string key, std::string texturePass,
		std::string modelPass, int lostHP)
		: Equipment(key, texturePass,modelPass, lostHP)
	{}

	void Execute() override;
};
#pragma endregion

//Š™
#pragma region Sickle 
class Sickle : public Equipment
{
public:

	Sickle(std::string key, std::string texturePass,
		std::string modelPass, int lostHP)
		: Equipment(key, texturePass, modelPass, lostHP)
	{}

	void Execute() override;
};
#pragma endregion

