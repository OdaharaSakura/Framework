#pragma once


class DebugManager
{
private:
	static Renderer* m_Renderer;

	static class  Player* m_Player;
	static bool m_IsCollisionDrawActive;

	static class  Polygon2D* m_Polygon2D;
	static class FPSCounter* m_FpsCounter;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static bool GetIsCollisionDrawActive() { return m_IsCollisionDrawActive; }
};