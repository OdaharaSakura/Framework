#pragma once

#include <iostream>
#include <chrono>
class Time 
{
private:

	class DirectWrite* write;
	std::string testtext;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	
	}
