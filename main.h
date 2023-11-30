#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX


#pragma warning(push)
#pragma warning(disable:4005)

#include <dwrite.h>  
#include <D2D1.h>
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <functional>

#include <d3d11.h>
#include <d3dx9.h>//DirectXÅ@ver9
#include <d3dx11.h>

#pragma warning(pop)

#pragma comment (lib, "dxgi.lib")
#pragma comment(lib,"d2d1.lib") 
#pragma comment(lib,"dwrite.lib") 
#pragma comment (lib, "imm32.lib")

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")


  



#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)

HWND GetWindow();


