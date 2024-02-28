#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState: register(s0);

//ブルーム 輝度が強すぎて光が周りに漏れる現象
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//普通にテクスチャを取得して処理対象のピクセルの色と乗算しておく
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse *= In.Diffuse;//頂点色と合成して出力
	float4 bloom = 0.0; //ブルーム処理の結果を格納する変数

	//画面サイズ X960 Y540とした場合
    for (int y = -9; y < 10; y++) //上下は±12ピクセルの範囲
	{
		for (int x = -4; x < 5; x++) //左右は±3ピクセルの範囲
		{//式中の値の3を調節すると光の範囲が変化する
			float2 texCoord = In.TexCoord +
				float2(x * 4 / 1280.0, y * 9 / 720.0); //テクスチャ座標をずらす
			float4 color = g_Texture.Sample(g_SamplerState, texCoord);
			//明度を計算
			float bright = color.r * 0.299 + color.g * 0.587 + color.b * 0.114;

			if (x != 0 || y != 0)
			{
				bloom -= color / (x * x + y * y);//距離によって減衰
			}
		}
	}
	outDiffuse.rgb += bloom * 0.05f;//結果を加算
}
