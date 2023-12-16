
#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);
Texture2D g_TextureEnv : register(t1);
TextureCube g_TextureEnvCube : register(t2);//キューブマップ受け取り

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//法線を正規化して格納する
	float4 normal = normalize(In.Normal);

	//ランバート
	float light = -dot(Light.Direction.xyz, normal.xyz);
	light = saturate(light);

	//視線ベクトルを作る
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev);

	//反射ベクトルを作る
	float3 refv = reflect(eyev, normal.xyz);
	refv = normalize(refv);

	////反射ベクトルから環境マッピング用のテクスチャ座標を作成する
	//float2 envTexCoord;
	//envTexCoord.x = -refv.x * 0.5 + 0.5;
	//envTexCoord.y = -refv.y * 0.5 + 0.5;

	////テクスチャバイアス指定付きでのテクスチャの取得
	//float4 EnvTexColor = g_TextureEnv.SampleBias(g_SamplerState, envTexCoord, 0.0f);
	// 

	float4 EnvTexColor = g_TextureEnvCube.Sample(g_SamplerState, refv);


	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);


	//スフィアマップからサンプリングした色を加算合成する
	outDiffuse.rgb = (EnvTexColor.rgb * 0.9) + (outDiffuse.rgb * 0.5); //テクスチャ＊頂点色＊明るさ

    outDiffuse.a *= In.Diffuse.a;


}
