//
//#include "common.hlsl"
//
//Texture2D g_Texture : register(t0);
//SamplerState g_SamplerState : register(s0);
//Texture2D g_TextureToon : register(t1);
//
//void main(in PS_IN In, out float4 outDiffuse : SV_Target)
//{
//	//法線を正規化して格納する
//	float4 normal = normalize(In.Normal);
//
//	float light = -dot(Light.Direction.xyz, normal.xyz);
//	light = saturate(light);
//	light = clamp(light, 0.035, 0.965);
//
//	////プログラム版 明るさをセル塗り風に変換 if文でlightの値を3段階に調整
//	//if (light > 0.6)
//	//	light = 1.0;
//	//else if (light > 0.4)
//	//	light = 0.8;
//	//else
//	//	light = 0.6;
//
//	float2 uv = light;
//	float3 toon;
//	uv.x += param.x; //C言語から受け取る数値を使って座標をずらす
//
//	toon = g_TextureToon.Sample(g_SamplerState, uv); //明るさを取得
//
//
//	//テクスチャから色をサンプリングする
//    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
//
//	outDiffuse.rgb *= toon; //テクスチャ＊頂点色＊明るさ
//
//    outDiffuse.a *= In.Diffuse.a;
//
//	//エッジの作成
//	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
//	eyev = normalize(eyev);
//	
//	//outDiffuse.rgb *= saturate(In.Diffuse.rgb * light); //テクスチャ＊頂点色＊明るさ
//	
//	float d = dot(eyev, normal.xyz); //法線と視線ベクトルの内積
//	if (d > -0.1) //dの値を判定
//	{
//		outDiffuse.rgb *= 0.2; //適当な閾値で明度を落とす
//	}
//
//
//}
