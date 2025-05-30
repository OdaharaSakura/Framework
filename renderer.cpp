
#include "renderer.h"
#include <io.h>


D3D_FEATURE_LEVEL       Renderer::m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device* Renderer::m_Device{};
ID3D11DeviceContext* Renderer::m_DeviceContext{};
IDXGISwapChain* Renderer::m_SwapChain{};
ID3D11RenderTargetView* Renderer::m_RenderTargetView{};
ID3D11DepthStencilView* Renderer::m_DepthStencilView{};

ID3D11Buffer* Renderer::m_WorldBuffer{};
ID3D11Buffer* Renderer::m_ViewBuffer{};
ID3D11Buffer* Renderer::m_ProjectionBuffer{};
ID3D11Buffer* Renderer::m_MaterialBuffer{};
ID3D11Buffer* Renderer::m_LightBuffer{};
ID3D11Buffer* Renderer::m_CameraBuffer{};
ID3D11Buffer* Renderer::m_ParameterBuffer{};
ID3D11Buffer* Renderer::m_DissolveBuffer{};


ID3D11DepthStencilState* Renderer::m_DepthStateEnable{};
ID3D11DepthStencilState* Renderer::m_DepthStateDisable{};


ID3D11BlendState* Renderer::m_BlendState{};
ID3D11BlendState* Renderer::m_BlendStateATC{};

ID3D11RenderTargetView* m_BGRenderTargetView{};
ID3D11ShaderResourceView* m_BGShaderResourceView{};

ID3D11DepthStencilView* Renderer::m_DepthShadowDepthStencilView{};
ID3D11ShaderResourceView* Renderer::m_DepthShadowShaderResourceView{};

ID3D11Texture2D* Renderer::m_ReflectTexture{};
ID3D11RenderTargetView* Renderer::m_ReflectRenderTargetView{};
ID3D11DepthStencilView* Renderer::m_ReflectDepthStencilView{};
ID3D11Texture2D* Renderer::m_CubeReflectTexture{};
ID3D11ShaderResourceView* Renderer::m_CubeReflectShaderResourceView{};

ID3D11RenderTargetView* Renderer::m_PPRenderTargetView{};
ID3D11ShaderResourceView* Renderer::m_PPShaderResourceView{};

ID3D11RenderTargetView* Renderer::m_LuminanceRenderTargetView{};
ID3D11ShaderResourceView* Renderer::m_LuminanceShaderResourceView{};
ID3D11DepthStencilView* Renderer::m_LuminanceDepthStencilView{};
ID3D11RenderTargetView* Renderer::m_BloomRenderTargetView[4]{};
ID3D11ShaderResourceView* Renderer::m_BloomShaderResourceView[4]{};
ID3D11DepthStencilView* Renderer::m_BloomDepthStencilView[4]{};


void Renderer::Init()
{
	HRESULT hr = S_OK;




	// デバイス、スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = GetWindow();
	swapChainDesc.SampleDesc.Count = 1;//8;//1->8マルチサンプルアンチエイリアシング(zバッファのみ8ピクセルで計算)
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_SwapChain,
		&m_Device,
		&m_FeatureLevel,
		&m_DeviceContext);



	// レンダーターゲットビュー作成
	ID3D11Texture2D* renderTarget{};
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	m_Device->CreateRenderTargetView(renderTarget, NULL, &m_RenderTargetView);
	renderTarget->Release();


	// デプスステンシルバッファ作成
	ID3D11Texture2D* depthStencile{};
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;//DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);

	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;//D3D11_DSV_DIMENSION_TEXTURE2D→D3D11_DSV_DIMENSION_TEXTURE2DMSマルチサンプルアンチエイリアシングに設定
	depthStencilViewDesc.Flags = 0;
	m_Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthStencilView);
	depthStencile->Release();


	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);





	// ビューポート設定
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)SCREEN_WIDTH;
	viewport.Height = (FLOAT)SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &viewport);



	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;

	ID3D11RasterizerState* rs;
	m_Device->CreateRasterizerState(&rasterizerDesc, &rs);

	m_DeviceContext->RSSetState(rs);




	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	m_Device->CreateBlendState(&blendDesc, &m_BlendState);

	blendDesc.AlphaToCoverageEnable = TRUE;
	m_Device->CreateBlendState(&blendDesc, &m_BlendStateATC);

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_DeviceContext->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);





	// デプスステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateEnable);//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateDisable);//深度無効ステート

	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);




	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	//D3D11_FILTER_ANISOTROPIC//高画質
	//D3D11_FILTER_MIN_MAG_MIP_POINT//低解像度
	// D3D11_FILTER_MIN_MAG_MIP_LINEAR//他のゲームエンジンでは、トライリニアフィルタリング
	//ミップマップ

	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;//テクスチャをどのように貼るか
	//D3D11_TEXTURE_ADDRESS_WRAP//テクスチャ座標の0-1の範囲外にも繰り返しポリゴンを張る
	//D3D11_TEXTURE_ADDRESS_CLAMP//端を引き延ばして貼る
	//D3D11_TEXTURE_ADDRESS_BORDER//0-1の範囲内でしか貼らない
	//D3D11_TEXTURE_ADDRESS_MIRROR//鏡合わせで貼る
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 4;//16が最大//GPUによって対応してないものもある、無難なのは4
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	//samplerDesc.MaxLODミップマップの何段階目まで使うか0は128*128のみ

	ID3D11SamplerState* samplerState{};
	m_Device->CreateSamplerState(&samplerDesc, &samplerState);

	m_DeviceContext->PSSetSamplers(0, 1, &samplerState);

	// 比較サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDescCompare;
	ZeroMemory(&samplerDescCompare, sizeof(samplerDescCompare));
	samplerDescCompare.Filter = D3D11_FILTER_COMPARISON_ANISOTROPIC;
	samplerDescCompare.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescCompare.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescCompare.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescCompare.MipLODBias = 0;
	samplerDescCompare.MaxAnisotropy = 1;
	samplerDescCompare.ComparisonFunc = D3D11_COMPARISON_GREATER;
	samplerDescCompare.MinLOD = 0;
	samplerDescCompare.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerStateCompare = NULL;
	m_Device->CreateSamplerState(&samplerDescCompare, &samplerStateCompare);
	m_DeviceContext->PSSetSamplers(1, 1, &samplerStateCompare);

	// 定数バッファ生成
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_WorldBuffer);
	m_DeviceContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ViewBuffer);
	m_DeviceContext->VSSetConstantBuffers(1, 1, &m_ViewBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ProjectionBuffer);
	m_DeviceContext->VSSetConstantBuffers(2, 1, &m_ProjectionBuffer);


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_MaterialBuffer);
	m_DeviceContext->VSSetConstantBuffers(3, 1, &m_MaterialBuffer);
	m_DeviceContext->PSSetConstantBuffers(3, 1, &m_MaterialBuffer);


	bufferDesc.ByteWidth = sizeof(LIGHT);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_LightBuffer);
	m_DeviceContext->VSSetConstantBuffers(4, 1, &m_LightBuffer);
	m_DeviceContext->PSSetConstantBuffers(4, 1, &m_LightBuffer);

	bufferDesc.ByteWidth = sizeof(CAMERA);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_CameraBuffer);
	m_DeviceContext->PSSetConstantBuffers(5, 1, &m_CameraBuffer);


	bufferDesc.ByteWidth = sizeof(PARAMETER);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ParameterBuffer);
	m_DeviceContext->VSSetConstantBuffers(6, 1, &m_ParameterBuffer);
	m_DeviceContext->PSSetConstantBuffers(6, 1, &m_ParameterBuffer);



	// ライト初期化
	LIGHT light{};
	light.Enable = true;
	light.Direction = D3DXVECTOR4(0.5f, -1.0f, 0.8f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.5f, 1.5f, 1.5f, 1.0f);
	SetLight(light);



	// マテリアル初期化
	MATERIAL material{};
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);


	{
		//シャドウバッファ作成
		ID3D11Texture2D* depthTexture = NULL;
		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(td));
		td.Width = SCREEN_WIDTH * 4;
		td.Height = SCREEN_HEIGHT * 4;
		td.MipLevels = 1;
		td.ArraySize = 1;
		td.Format = DXGI_FORMAT_R32_TYPELESS;//32bitの自由な形式のデータとする
		td.SampleDesc = textureDesc.SampleDesc;
		td.Usage = D3D11_USAGE_DEFAULT; // ↓デプス＆ステンシルバッファとして作成
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		td.CPUAccessFlags = 0;
		td.MiscFlags = 0;
		m_Device->CreateTexture2D(&td, NULL, &depthTexture);

		//デプスステンシルターゲットビュー作成
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = DXGI_FORMAT_D32_FLOAT;//ピクセルフォーマットは32BitFLOAT型
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		m_Device->CreateDepthStencilView(depthTexture, &dsvd,
			&m_DepthShadowDepthStencilView);

		//シェーダーリソースビュー作成
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(srvd));
		srvd.Format = DXGI_FORMAT_R32_FLOAT;//ピクセルフォーマットは32BitFLOAT型
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MipLevels = 1;
		m_Device->CreateShaderResourceView(depthTexture, &srvd,
			&m_DepthShadowShaderResourceView);

		depthTexture->Release();
	}

	//環境マップレンダリングテクスチャ作成
	{
		D3D11_TEXTURE2D_DESC tdEnv;
		ZeroMemory(&tdEnv, sizeof(tdEnv));
		tdEnv.ArraySize = 1;
		tdEnv.Width = 512;
		tdEnv.Height = 512;
		tdEnv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tdEnv.Usage = D3D11_USAGE_DEFAULT;
		tdEnv.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tdEnv.SampleDesc = swapChainDesc.SampleDesc;
		tdEnv.MiscFlags = 0;
		tdEnv.MipLevels = 1;
		m_Device->CreateTexture2D(&tdEnv, NULL, &m_ReflectTexture);
		D3D11_RENDER_TARGET_VIEW_DESC rtvd;
		ZeroMemory(&rtvd, sizeof(rtvd));
		rtvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		m_Device->CreateRenderTargetView(m_ReflectTexture, &rtvd, &m_ReflectRenderTargetView);
		ID3D11Texture2D* depthEnvTexture = NULL;
		ZeroMemory(&tdEnv, sizeof(tdEnv));
		tdEnv.Width = 512;
		tdEnv.Height = 512;
		tdEnv.MipLevels = 1;
		tdEnv.ArraySize = 1;
		tdEnv.Format = DXGI_FORMAT_D32_FLOAT;
		tdEnv.SampleDesc.Count = 1;
		tdEnv.SampleDesc.Quality = 0;
		tdEnv.Usage = D3D11_USAGE_DEFAULT;
		tdEnv.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		tdEnv.CPUAccessFlags = 0;
		tdEnv.MiscFlags = 0;
		m_Device->CreateTexture2D(&tdEnv, NULL, &depthEnvTexture);

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = DXGI_FORMAT_D32_FLOAT;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		m_Device->CreateDepthStencilView(depthEnvTexture, &dsvd, &m_ReflectDepthStencilView);
		depthEnvTexture->Release();
	}

	{
		D3D11_TEXTURE2D_DESC tdEnvCube;
		ZeroMemory(&tdEnvCube, sizeof(tdEnvCube));
		tdEnvCube.ArraySize = 6;
		tdEnvCube.Width = 512;
		tdEnvCube.Height = 512;
		tdEnvCube.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tdEnvCube.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tdEnvCube.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS | D3D11_RESOURCE_MISC_TEXTURECUBE;
		tdEnvCube.MipLevels = 1;
		tdEnvCube.Usage = D3D11_USAGE_DEFAULT;
		tdEnvCube.SampleDesc = swapChainDesc.SampleDesc;
		m_Device->CreateTexture2D(&tdEnvCube, NULL, &m_CubeReflectTexture);
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(srvd));
		srvd.Format = tdEnvCube.Format;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
		srvd.TextureCube.MipLevels = tdEnvCube.MipLevels;
		srvd.TextureCube.MostDetailedMip = 0;
		m_Device->CreateShaderResourceView(m_CubeReflectTexture, &srvd, &m_CubeReflectShaderResourceView);
	}

	{
		//テクスチャー作成
		ID3D11Texture2D* ppTexture = NULL;
		D3D11_TEXTURE2D_DESC td; //テクスチャ作成用デスクリプタ構造体変数
		ZeroMemory(&td, sizeof(td)); //構造体を０初期化

		td.Width = swapChainDesc.BufferDesc.Width; //構造体sdはInit関数の最初で作られている。
		td.Height = swapChainDesc.BufferDesc.Height;//バックバッファの情報が格納されている
		td.MipLevels = 1;//ミップマップの数 0は限界まで作る
		td.ArraySize = 1;
		td.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //ピクセルフォーマット
		td.SampleDesc = swapChainDesc.SampleDesc;
		td.Usage = D3D11_USAGE_DEFAULT;
		//使用法のフラグを設定
		td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		td.CPUAccessFlags = 0;
		td.MiscFlags = 0;
		//構造体の設定に従ってテクスチャ領域を作成
		m_Device->CreateTexture2D(&td, NULL, &ppTexture);





		//レンダーターゲットビュー作成
		D3D11_RENDER_TARGET_VIEW_DESC rtvd;
		ZeroMemory(&rtvd, sizeof(rtvd));
		rtvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		m_Device->CreateRenderTargetView(ppTexture, &rtvd,
			&m_PPRenderTargetView);

		//シェーダーリソースビュー作成
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(srvd));
		srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MipLevels = 1;
		m_Device->CreateShaderResourceView(ppTexture, &srvd,
			&m_PPShaderResourceView);
		ppTexture->Release();

		{
			//テクスチャー作成
			ID3D11Texture2D* luminanceTexture = NULL;
			D3D11_TEXTURE2D_DESC td; //テクスチャ作成用デスクリプタ構造体変数
			ZeroMemory(&td, sizeof(td)); //構造体を０初期化

			td.Width = SCREEN_WIDTH / 2; //構造体sdはInit関数の最初で作られている。
			td.Height = SCREEN_HEIGHT / 2;//バックバッファの情報が格納されている
			td.MipLevels = 1;//ミップマップの数 0は限界まで作る
			td.ArraySize = 1;
			td.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //ピクセルフォーマット
			td.SampleDesc = swapChainDesc.SampleDesc;
			td.Usage = D3D11_USAGE_DEFAULT;
			//使用法のフラグを設定
			td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			td.CPUAccessFlags = 0;
			td.MiscFlags = 0;
			//構造体の設定に従ってテクスチャ領域を作成
			m_Device->CreateTexture2D(&td, NULL, &luminanceTexture);



			//レンダーターゲットビュー作成
			D3D11_RENDER_TARGET_VIEW_DESC rtvd;
			ZeroMemory(&rtvd, sizeof(rtvd));
			rtvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			m_Device->CreateRenderTargetView(luminanceTexture, &rtvd,
				&m_LuminanceRenderTargetView);

			//ステンシルターゲット作成
			D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
			ZeroMemory(&dsvd, sizeof(dsvd));
			dsvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			dsvd.Flags = 0;
			m_Device->CreateDepthStencilView(luminanceTexture, &dsvd, &m_LuminanceDepthStencilView);




			//シェーダーリソースビュー作成
			D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
			ZeroMemory(&srvd, sizeof(srvd));
			srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvd.Texture2D.MipLevels = 1;
			m_Device->CreateShaderResourceView(luminanceTexture, &srvd,
				&m_LuminanceShaderResourceView);
			luminanceTexture->Release();
		}

		for (int i = 0; i < 4; i++)
		{
			//テクスチャー作成
			ID3D11Texture2D* bloomTexture = NULL;
			D3D11_TEXTURE2D_DESC td; //テクスチャ作成用デスクリプタ構造体変数
			ZeroMemory(&td, sizeof(td)); //構造体を０初期化



			td.Width = SCREEN_WIDTH / pow(2, (i + 2)); //構造体sdはInit関数の最初で作られている。
			td.Height = SCREEN_HEIGHT / pow(2, (i + 2));//バックバッファの情報が格納されている
			td.MipLevels = 1;//ミップマップの数 0は限界まで作る
			td.ArraySize = 1;
			td.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //ピクセルフォーマット
			td.SampleDesc = swapChainDesc.SampleDesc;
			td.Usage = D3D11_USAGE_DEFAULT;
			//使用法のフラグを設定
			td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			td.CPUAccessFlags = 0;
			td.MiscFlags = 0;
			//構造体の設定に従ってテクスチャ領域を作成
			m_Device->CreateTexture2D(&td, NULL, &bloomTexture);


			//レンダーターゲットビュー作成
			D3D11_RENDER_TARGET_VIEW_DESC rtvd;
			ZeroMemory(&rtvd, sizeof(rtvd));
			rtvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			m_Device->CreateRenderTargetView(bloomTexture, &rtvd,
				&m_BloomRenderTargetView[i]);

			//ステンシルターゲット作成
			D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
			ZeroMemory(&dsvd, sizeof(dsvd));
			dsvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			dsvd.Flags = 0;
			m_Device->CreateDepthStencilView(bloomTexture, &dsvd, &m_BloomDepthStencilView[i]);

			//シェーダーリソースビュー作成
			D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
			ZeroMemory(&srvd, sizeof(srvd));
			srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvd.Texture2D.MipLevels = 1;
			m_Device->CreateShaderResourceView(bloomTexture, &srvd,
				&m_BloomShaderResourceView[i]);



			bloomTexture->Release();
		}
	}

	//setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig config;
	config.MergeMode = true;
	////io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo UI 標準.ttc", 18.0f, &config, io.Fonts->GetGlyphRangesJapanese());


	ImGui::StyleColorsDark();


	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(m_Device, m_DeviceContext);

}



void Renderer::Uninit()
{

	if (m_WorldBuffer != nullptr)m_WorldBuffer->Release();
	if (m_ViewBuffer != nullptr)m_ViewBuffer->Release();
	if (m_ProjectionBuffer != nullptr)m_ProjectionBuffer->Release();
	if (m_LightBuffer != nullptr)m_LightBuffer->Release();
	if (m_MaterialBuffer != nullptr)m_MaterialBuffer->Release();
	if (m_CameraBuffer != nullptr)m_CameraBuffer->Release();
	if (m_ParameterBuffer != nullptr)m_ParameterBuffer->Release();
	if (m_DissolveBuffer != nullptr)m_DissolveBuffer->Release();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();


	m_DeviceContext->ClearState();
	m_RenderTargetView->Release();
	m_SwapChain->Release();
	m_DeviceContext->Release();
	m_Device->Release();

}




void Renderer::Begin()
{
	//デフォルトのバックバッファと深度バッファへ復帰させておく
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView,
		m_DepthStencilView);
	// バックバッファクリア
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, clearColor);//クリアカラーに画面表示
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	/*ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();*/
}



void Renderer::End()
{
	/*ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());*/

	m_SwapChain->Present(1, 0);
}




void Renderer::SetDepthEnable(bool Enable)
{
	if (Enable)
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);
	else
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateDisable, NULL);

}



void Renderer::SetATCEnable(bool Enable)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (Enable)
		m_DeviceContext->OMSetBlendState(m_BlendStateATC, blendFactor, 0xffffffff);
	else
		m_DeviceContext->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);

}

void Renderer::SetWorldViewProjection2D()
{
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranspose(&world, &world);

	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);

	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	D3DXMatrixTranspose(&projection, &projection);
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);

}


void Renderer::SetWorldMatrix(D3DXMATRIX* WorldMatrix)
{
	D3DXMATRIX world;
	D3DXMatrixTranspose(&world, WorldMatrix);
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);
}

void Renderer::SetViewMatrix(D3DXMATRIX* ViewMatrix)
{
	D3DXMATRIX view;
	D3DXMatrixTranspose(&view, ViewMatrix);
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
}

void Renderer::SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix)
{
	D3DXMATRIX projection;
	D3DXMatrixTranspose(&projection, ProjectionMatrix);
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}



void Renderer::SetMaterial(MATERIAL Material)
{
	m_DeviceContext->UpdateSubresource(m_MaterialBuffer, 0, NULL, &Material, 0, 0);
}

void Renderer::SetLight(LIGHT Light)
{
	//シェーダー側の都合上で行列を転置しておく
	D3DXMatrixTranspose(&Light.ViewMatrix, &Light.ViewMatrix);
	D3DXMatrixTranspose(&Light.ProjectionMatrix, &Light.ProjectionMatrix);
	m_DeviceContext->UpdateSubresource(m_LightBuffer, 0, NULL, &Light, 0, 0);
}

void Renderer::SetCameraPosition(CAMERA Camera)
{
	m_DeviceContext->UpdateSubresource(m_CameraBuffer, 0, NULL, &Camera, 0, 0);
}

void Renderer::SetParameter(PARAMETER param)
{
	m_DeviceContext->UpdateSubresource(m_ParameterBuffer, 0, NULL, &param, 0, 0);
}

void Renderer::SetDissolve(DISSOLVE dissolve)
{
	m_DeviceContext->UpdateSubresource(m_DissolveBuffer, 0, NULL, &dissolve, 0, 0);
}





void Renderer::CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName)
{

	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	m_Device->CreateVertexShader(buffer, fsize, NULL, VertexShader);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,		0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  4 * 9, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	4 * 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0,	4 * 16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	m_Device->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		VertexLayout);

	delete[] buffer;
}


// ピクセルシェーダ生成
void Renderer::CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName)
{
	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	m_Device->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;
}

void Renderer::BeginPP()
{
	//レンダーターゲットをバックバッファに戻す
	m_DeviceContext->OMSetRenderTargets(1, &m_PPRenderTargetView, m_DepthStencilView);

	//バックバッファクリア
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };//赤
	m_DeviceContext->ClearRenderTargetView(m_PPRenderTargetView, ClearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::BeginLuminance()
{
	//レンダーターゲットをバックバッファに戻す
	m_DeviceContext->OMSetRenderTargets(1, &m_LuminanceRenderTargetView, m_LuminanceDepthStencilView);

	//バックバッファクリア
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };//赤
	m_DeviceContext->ClearRenderTargetView(m_LuminanceRenderTargetView, ClearColor);
	m_DeviceContext->ClearDepthStencilView(m_LuminanceDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::BeginBloom(int index)
{
	//レンダーターゲットをバックバッファに戻す
	m_DeviceContext->OMSetRenderTargets(1, &m_BloomRenderTargetView[index], m_BloomDepthStencilView[index]);

	//バックバッファクリア
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };//赤
	m_DeviceContext->ClearRenderTargetView(m_BloomRenderTargetView[index], ClearColor);
	m_DeviceContext->ClearDepthStencilView(m_BloomDepthStencilView[index], D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::SetDefaultViewPort()
{
	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &vp);
}

void Renderer::SetDepthViewPort()
{
	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH * 4;
	vp.Height = (FLOAT)SCREEN_HEIGHT * 4;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 10;
	vp.TopLeftY = 10;
	m_DeviceContext->RSSetViewports(1, &vp);
}

void Renderer::SetReflectViewport(void)
{
	D3D11_VIEWPORT vp;
	vp.Width = 512;
	vp.Height = 512;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &vp);

}

void Renderer::SetLuminanceViewport()
{
	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH / 2;
	vp.Height = (FLOAT)SCREEN_HEIGHT / 2;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &vp);
}

void Renderer::SetBloomViewport(int index)
{
	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH / pow(2, (index + 2));
	vp.Height = (FLOAT)SCREEN_HEIGHT / pow(2, (index + 2));
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &vp);
}

