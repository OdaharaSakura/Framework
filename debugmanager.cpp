#include "main.h"
#include "renderer.h"
#include "debugManager.h"
#include "manager.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"
#include "player.h"
#include "polygon2D.h"


#include <string>

Renderer* DebugManager::m_Renderer{};
Player* DebugManager::m_Player{};
Polygon2D* DebugManager::m_Polygon2D{};
FPSCounter* DebugManager::m_FpsCounter{};

bool show_demo_window = true;
bool show_another_window = false;

void DebugManager::Init()
{
	m_Renderer = Manager::GetRenderer();

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(m_Renderer->GetDevice(), m_Renderer->GetDeviceContext());

	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF("c:\Windows\Fonts\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
}

void DebugManager::Uninit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void DebugManager::Update()
{
	m_Player = Manager::GetScene()->GetGameObject<Player>();
	m_Polygon2D = Manager::GetScene()->GetGameObject<Polygon2D>();
}

void DebugManager::Draw()
{
	// フレームの開始
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);

	// ImGuiウィンドウやコントロールの作成と更新
	ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_Once);
	ImGui::Begin("DebugWindow", ((bool*)0), ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save")) {

            }
            if (ImGui::MenuItem("Load")) {

            }

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
	
	ImGui::Text("\nPlayer");
	D3DXVECTOR3 i = m_Player->GetPosition();
	D3DXVECTOR3 r = m_Player->GetRotation();
	D3DXVECTOR3 s = m_Player->GetScale();

	ImGui::InputFloat("positionX", &i.x);
	ImGui::InputFloat("positionY", &i.y);
	ImGui::InputFloat("positionZ", &i.z);


	const char* cd = "aaaaaaaaaaaaaaa";
	char c = *cd;

	ImGui::InputTextMultiline("textbox 1", &c, sizeof(c));
	if (ImGui::Button("InputText")) {
	}

	ImGui::End();

	// ImGuiコード
	//フレームの描画
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
