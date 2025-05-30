#pragma once
#include "main.h"

// 頂点構造体
struct VERTEX_3D
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR3 Tangent;
	D3DXVECTOR3 Binormal;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR2 TexCoord;
};


// マテリアル(材質)構造体
struct MATERIAL
{
	D3DXCOLOR	Ambient;	//環境光
	D3DXCOLOR	Diffuse;	//拡散光
	D3DXCOLOR	Specular;	//反射光
	D3DXCOLOR	Emission;	//自己発光色
	float		Shininess;	//反射光の強度
	BOOL		TextureEnable;
	float		Dummy[2];//16byte境界用
};

// マテリアル構造体
struct DX11_MODEL_MATERIAL
{
	MATERIAL		Material;
	class CTexture* Texture;
};


// 描画サブセット構造体
struct DX11_SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	DX11_MODEL_MATERIAL	Material;
};


struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;
	D3DXMATRIX ViewMatrix;			//追加　ライトカメラ行列
	D3DXMATRIX ProjectionMatrix;	//追加　ライトプロジェクション行列
};

struct CAMERA
{
	D3DXVECTOR4	Position;
	D3DXVECTOR4	FogParam;//x FogStart, y FogEnd, z FogHeight
	D3DXCOLOR	FogColor;
	D3DXCOLOR	GroundFogColor;
};

struct PARAMETER
{
	D3DXVECTOR4 hitpoint;
	D3DXCOLOR	baseColor;//HPバーの色
	D3DXCOLOR	lostColor;//減少したHPバーの色
	D3DXCOLOR	diffColor;//一時表示HPバーの色
};

struct DISSOLVE
{
	float dissolveThreshold;
	float dissolveRange;
};


class VertexBuffer;
class IndexBuffer;
class Texture;



class Renderer
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device* m_Device;
	static ID3D11DeviceContext* m_DeviceContext;
	static IDXGISwapChain* m_SwapChain;
	static IDXGISwapChain* m_SwapChainShadow;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11Buffer* m_WorldBuffer;
	static ID3D11Buffer* m_ViewBuffer;
	static ID3D11Buffer* m_ProjectionBuffer;
	static ID3D11Buffer* m_MaterialBuffer;
	static ID3D11Buffer* m_LightBuffer;
	static ID3D11Buffer* m_CameraBuffer;
	static ID3D11Buffer* m_ParameterBuffer;
	static ID3D11Buffer* m_DissolveBuffer;


	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

	static ID3D11BlendState* m_BlendState;
	static ID3D11BlendState* m_BlendStateATC;

	static ID3D11RenderTargetView* m_BGRenderTargetView;
	static ID3D11ShaderResourceView* m_BGShaderResourceView;

	static ID3D11DepthStencilView* m_DepthShadowDepthStencilView;//
	static ID3D11ShaderResourceView* m_DepthShadowShaderResourceView;//

	static ID3D11Texture2D* m_ReflectTexture;
	static ID3D11RenderTargetView* m_ReflectRenderTargetView;
	static ID3D11DepthStencilView* m_ReflectDepthStencilView;
	static ID3D11Texture2D* m_CubeReflectTexture;
	static ID3D11ShaderResourceView* m_CubeReflectShaderResourceView;

	static ID3D11RenderTargetView* m_PPRenderTargetView;
	static ID3D11ShaderResourceView* m_PPShaderResourceView;

	static ID3D11RenderTargetView* m_LuminanceRenderTargetView;
	static ID3D11ShaderResourceView* m_LuminanceShaderResourceView;
	static ID3D11DepthStencilView* m_LuminanceDepthStencilView;

	static ID3D11RenderTargetView* m_BloomRenderTargetView[4];
	static ID3D11ShaderResourceView* m_BloomShaderResourceView[4];
	static ID3D11DepthStencilView* m_BloomDepthStencilView[4];


public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetATCEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);


	static void SetCameraPosition(CAMERA Camera);
	static void SetParameter(PARAMETER param);
	static void SetDissolve(DISSOLVE dissolve);


	static ID3D11Device* GetDevice(void) { return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }
	static IDXGISwapChain* GetSwapChain() { return m_SwapChain; }
	static ID3D11RenderTargetView* GetRenderTargetView() { return m_RenderTargetView; }

	static ID3D11Texture2D* GetReflectTexture(void) { return m_ReflectTexture; }
	static ID3D11Texture2D* GetCubeReflectTexture(void) { return m_CubeReflectTexture; }
	static ID3D11ShaderResourceView** GetCubeReflectShaderResourceView(void){ return &m_CubeReflectShaderResourceView; }

	static ID3D11ShaderResourceView** GetPPTexture() { return &m_PPShaderResourceView; }
	static ID3D11ShaderResourceView** GetLuminanceTexture() { return &m_LuminanceShaderResourceView; }
	static ID3D11ShaderResourceView** GetBloomTexture(int index) { return &m_BloomShaderResourceView[index]; }


	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

	static ID3D11ShaderResourceView* GetDepthShadowTexture(){ return m_DepthShadowShaderResourceView; }

	static void BeginDepth()//新規関数追加
	{
		//シャドウバッファを深度バッファに設定し、内容を1で塗りつぶしておく
		m_DeviceContext->OMSetRenderTargets(0, NULL, m_DepthShadowDepthStencilView);
		m_DeviceContext->ClearDepthStencilView(m_DepthShadowDepthStencilView,
			D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	static void BeginCube()
	{
		//レンダリングターゲットをバックバッファに戻す
		m_DeviceContext->OMSetRenderTargets(1, &m_ReflectRenderTargetView, m_ReflectDepthStencilView);
		//画面クリア
		float ClearColor[4] = { 0.0f, 0.5f, 0.0f, 1.0f };
		m_DeviceContext->ClearRenderTargetView(m_ReflectRenderTargetView, ClearColor);
		m_DeviceContext->ClearDepthStencilView(m_ReflectDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	static void BeginPP();
	static void BeginLuminance();
	static void BeginBloom(int index);

	static void SetDefaultViewPort();
	static void SetDepthViewPort();
	static void SetReflectViewport();
	static void SetLuminanceViewport();
	static void SetBloomViewport(int index);
};
