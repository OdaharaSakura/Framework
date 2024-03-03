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

//鍬
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

//鎌
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

//水の杖
#pragma region WaterWand
class WaterWand : public Equipment
{
public:
	
	WaterWand(std::string key, std::string texturePass,
				std::string modelPass, int lostHP)
		: Equipment(key, texturePass, modelPass, lostHP)
	{}

	void Execute() override;
};
#pragma endregion

//剣
#pragma region Sword
class Sword : public Equipment
{
public:

	Sword(std::string key, std::string texturePass,
		std::string modelPass, int lostHP)
		: Equipment(key, texturePass, modelPass, lostHP)
	{}

	void Execute() override;
};
#pragma endregion

//トマトの種
#pragma region TomatoSeed
class TomatoSeed : public Equipment
{
public:

	TomatoSeed(std::string key, std::string texturePass,
		std::string modelPass, int lostHP)
		: Equipment(key, texturePass, modelPass, lostHP)
	{}

	void Execute() override;
};
#pragma endregion

//人参の種
#pragma region CarrotSeed
class CarrotSeed : public Equipment
{
public:

	CarrotSeed(std::string key, std::string texturePass,
		std::string modelPass, int lostHP)
		: Equipment(key, texturePass, modelPass, lostHP)
	{}

	void Execute() override;
};
#pragma endregion
