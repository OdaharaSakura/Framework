#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by WSock.rc
//
#define IDD_DIALOG1                     101
#define IDC_BUTTON1                     1001
#define IDC_BUTTON2                     1002
#define IDC_EDIT1                       1003
#define IDC_EDIT2                       1004
#define IDC_EDIT3                       1005

#define _WINSOCKAPI_

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        102
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1006
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif


#pragma warning(push)
#pragma warning(disable:4005)
#include <d2d1.h>						// Direct2D
#include <DWrite.h>						// DirectWrite
#include <D3DX10math.h>					// 数学系ライブラリ
#include <stdio.h>
#include <wrl.h>						// ComPtr
#include <windows.h>
#include <assert.h>
#include <mmsystem.h>
#include <functional>

#include <d3d11.h>
#include <d3dx9.h>//DirectX　ver9
#include <d3dx11.h>

#pragma warning(pop)

#pragma comment (lib, "dxgi.lib")
#pragma comment(lib,"d2d1.lib")			// Direct2D用
#pragma comment(lib,"Dwrite.lib")		// DirectWrite用
#pragma comment (lib, "imm32.lib")
#pragma comment (lib,"Ws2_32.lib")

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")




#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)

HWND GetWindow();


