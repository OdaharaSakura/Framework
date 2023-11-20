#include "common.hlsl"

Texture2D g_Texture : register(t0);//通常テクスチャ
Texture2D g_TextureDepthShadow : register(t1);//シャドウマップ
SamplerState g_SamplerState : register(s0);
SamplerComparisonState  g_ShadowMapSampler : register(s1);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//日向での色＝普通のテクスチャ＊頂点色を作成しておく
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse *= In.Diffuse;
	In.ShadowPosition.xyz /= In.ShadowPosition.w; //正規化デバイス座標に変換
	In.ShadowPosition.x = In.ShadowPosition.x * 0.5f + 0.5f; //テクスチャ座標に変換
	In.ShadowPosition.y = (In.ShadowPosition.y * -0.5f) + 0.5f; //

	//シャドウマップテクスチャより、ライトカメラからピクセルまでの距離（深度値）を取得


	//float depth = g_TextureDepthShadow.Sample(g_SamplerState, shadowmapxy);



	if (In.ShadowPosition.x > 0.0f && In.ShadowPosition.x < 1.0f &&
		In.ShadowPosition.y > 0.0f && In.ShadowPosition.y < 1.0f)
	{
		float2 shadowmapxy = float2(In.ShadowPosition.x, In.ShadowPosition.y);
		float shadow = g_TextureDepthShadow.SampleCmpLevelZero(
			g_ShadowMapSampler,
			shadowmapxy,
			In.ShadowPosition.z
		);

		float3 shadowColor = outDiffuse.rgb * 0.5f;//色を暗くする
		outDiffuse.rgb = lerp(outDiffuse.rgb, shadowColor, shadow);
	}
}
