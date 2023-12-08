
#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//背景色を設定
	outDiffuse.rgb = float3(0.0f, 0.0f, 0.0f);
	
	//ワイプ用テクスチャからサンプリング(rgbaからrだけ抽出する)
	float dissolveValue = g_Texture.Sample(g_SamplerState, In.TexCoord);

	float threshold = dissolve.dissolveThreshold * (1.0f + dissolve.dissolveRange) - dissolve.dissolveRange;

	float rate = saturate((dissolveValue - threshold) / dissolve.dissolveRange);

	outDiffuse.a = rate;

	////fadein
	////step(x, y) → x <= y なら1を返す　そうでないなら0を返す
	//outDiffuse.a = step(param.dissolveThreshold, dissolveValue);

	////fadeout
	////step(y, x) → y <= x なら1を返す　そうでないなら0を返す
	//outDiffuse.a = step(dissolveValue, param.dissolveThreshold);
}
