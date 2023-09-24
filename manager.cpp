#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "input.h"
#include "game.h"
#include "game.h"
#include "test.h"
#include "audio.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

Scene* Manager::m_Scene{};//�ÓI�����o�ϐ��͍Đ錾���K�v
Scene* Manager::m_NextScene{};//�ÓI�����o�ϐ��͍Đ錾���K�v
Renderer* Manager::m_Renderer{};

bool Manager::m_IsGameFinish{};

void Manager::Init()
{
	m_Renderer = new Renderer();
	m_Renderer->Init();

	//ImGui::CreateContext();
	//ImGui_ImplWin32_Init(GetWindow());
	//ImGui_ImplDX11_Init(m_Renderer->GetDevice(), m_Renderer->GetDeviceContext());


	Input::Init();
	Audio::InitMaster();
	m_IsGameFinish = false;

	//m_Scene = new Title();
	//m_Scene->Init();
	SetScene<Test>();
}

void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	Audio::UninitMaster();
	Input::Uninit();
	//ImGui_ImplDX11_Shutdown();
	//ImGui_ImplWin32_Shutdown();
	//ImGui::DestroyContext();
	m_Renderer->Uninit();
}

void Manager::Update()
{
	Input::Update();
	if (m_NextScene)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}
		m_Scene = m_NextScene;
		m_Scene->Init();
		m_NextScene = nullptr;
	}

	m_Scene->Update();
}

void Manager::Draw()
{


	m_Renderer->Begin();


	m_Scene->Draw();

	// �t���[���̊J�n
	//ImGui_ImplDX11_NewFrame();
	//ImGui_ImplWin32_NewFrame();
	//ImGui::NewFrame();

	// ImGui�E�B���h�E��R���g���[���̍쐬�ƍX�V
	//ImGui::SetNextWindowSize(ImVec2(320, 100), ImGuiCond_Once);
	//ImGui::Begin("hoge", ((bool*)0), ImGuiWindowFlags_NoMove);
	//ImGui::Text("fugafuga");
	//ImGui::End();

// ImGui�R�[�h
	// �t���[���̕`��
	//ImGui::Render();
	//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	m_Renderer->End();

}
