//#include "main.h"
//#include "renderer.h"
//#include "debugManager.h"
//#include "manager.h"
//#include "../imgui/imgui_impl_dx11.h"
//#include "../imgui/imgui_impl_win32.h"
//
//Renderer* DebugManager::m_Renderer{};
//
//bool show_demo_window = true;
//bool show_another_window = false;
//
//void DebugManager::Init()
//{
//	m_Renderer = Manager::GetRenderer();
//
//	ImGui::CreateContext();
//	ImGui_ImplWin32_Init(GetWindow());
//	ImGui_ImplDX11_Init(m_Renderer->GetDevice(), m_Renderer->GetDeviceContext());
//}
//
//void DebugManager::Uninit()
//{
//	ImGui_ImplDX11_Shutdown();
//	ImGui_ImplWin32_Shutdown();
//	ImGui::DestroyContext();
//}
//
//void DebugManager::Update()
//{
//
//}
//
//void DebugManager::Draw()
//{
//	// フレームの開始
//	ImGui_ImplDX11_NewFrame();
//	ImGui_ImplWin32_NewFrame();
//	ImGui::NewFrame();
//
//	// ImGuiウィンドウやコントロールの作成と更新
//	ImGui::SetNextWindowSize(ImVec2(320, 100), ImGuiCond_Once);
//	ImGui::Begin("hoge", ((bool*)0), ImGuiWindowFlags_NoResize);
//	ImGui::Text("fugafuga");
//	ImGui::End();
//
//	// ImGuiコード
//	//フレームの描画
//	ImGui::Render();
//	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
//}
