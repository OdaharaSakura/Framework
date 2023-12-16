#pragma once
#include "gameObject.h"
#include <string>
#include <vector>

class GameObject;


class Sphere : public GameObject
{
private:

	class Model* m_Model{};


	ID3D11ShaderResourceView* m_TextureEnvCube = NULL;

	float m_Radius = 1.0f;
	float m_ScaleOffset = 100.0f;


public:

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


