
#include "common.hlsl"


Texture2D g_Texture1 : register(t0); //テクスチャ0番
Texture2D g_Texture2 : register(t1); //テクスチャ1番
SamplerState	g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);	
	//outDiffuse *= In.Diffuse;

	////αクリップ（α値が0だと描画しない）
	//if (outDiffuse.a < 0.1f) discard;

	//サンプリングして色を取得
	float4 tex1 = g_Texture1.Sample(g_SamplerState, In.TexCoord);

	//サンプリングして色を取得
	float4 tex2 = g_Texture2.Sample(g_SamplerState, In.TexCoord);

	////αブレンディング
	//outDiffuse.rgb = tex1.rgb * (1.0f - tex2.a) + tex2.rgb * tex2.a;
	//outDiffuse.a = In.Diffuse.a;

	// 両方のテクスチャのアルファ値を取得
	float alpha1 = tex1.a;
	float alpha2 = tex2.a;

	// 重なった部分のアルファ値を計算
	float blendedAlpha = alpha1 + alpha2 * (1.0 - alpha1);

	// アルファブレンディング
	outDiffuse.rgb = tex1.rgb * (1.0 - alpha2) + tex2.rgb * alpha2;
	outDiffuse.a = blendedAlpha;

	// もしアルファ値が一定以下なら描画しない（透明部分）
	if (outDiffuse.a < 0.1f)
		discard;


	//outDiffuse.rgb = tex1.rgb;	//石のテクスチャで
	//outDiffuse.a = tex1.a;		//ツリーの形で

	//outDiffuse *= In.Diffuse; //デフューズ(頂点の明るさ)を合成

		//グレースケール変換
	//float gray;
	//gray = 0.299 * outDiffuse.r + 0.587 * outDiffuse.g + 0.114 * outDiffuse.b;
	//outDiffuse.r = gray;
	//outDiffuse.g = gray;
	//outDiffuse.b = gray;

	//セピア変換
	//float4 sepia = float4(0.960, 0.784, 0.580, 1.0);
	//outDiffuse *= sepia;

}
