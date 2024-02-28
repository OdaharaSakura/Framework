#include "main.h"
#include "renderer.h"
#include "debugManager.h"
#include "manager.h"

#include "player.h"
#include "polygon2D.h"


#include <string>

Renderer* DebugManager::m_Renderer{};
Player* DebugManager::m_Player{};
bool DebugManager::m_IsCollisionDrawActive{};
Polygon2D* DebugManager::m_Polygon2D{};
FPSCounter* DebugManager::m_FpsCounter{};

bool show_demo_window = true;
bool show_another_window = false;

void DebugManager::Init()
{
	//m_Renderer = Manager::GetRenderer();

	//ImGui::CreateContext();
	//ImGui_ImplWin32_Init(GetWindow());
	//ImGui_ImplDX11_Init(m_Renderer->GetDevice(), m_Renderer->GetDeviceContext());
}

void DebugManager::Uninit()
{
	//ImGui_ImplDX11_Shutdown();
	//ImGui_ImplWin32_Shutdown();
	//ImGui::DestroyContext();
}

void DebugManager::Update()
{
	m_Player = Manager::GetScene()->GetGameObject<Player>();

}

void DebugManager::Draw()
{
	// フレームの開始
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	
	if(m_Player != nullptr)m_Player->GetDebugData();

	ImGui::Begin("Collider");
	ImGui::Checkbox("Active", &m_IsCollisionDrawActive);
	ImGui::End();

	// ImGuiコード
	//フレームの描画
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
