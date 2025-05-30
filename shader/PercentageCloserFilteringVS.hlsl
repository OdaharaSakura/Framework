#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp; //いつもの処理だが
	wvp = mul(World, View); //1パス目はライトカメラの行列
	wvp = mul(wvp, Projection); //2パス目は通常カメラの行列が設定される
	Out.Position = mul(In.Position, wvp);//頂点座標をワールド変換して出力
	float4 worldNormal, normal; //法線のワールド変換
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);
	Out.Normal = worldNormal; //法線を出力

	//光源処理
	float light = -dot(Light.Direction.xyz, worldNormal.xyz);
    light = saturate(light * 1.5f);
    Out.Diffuse = In.Diffuse * Material.Diffuse * light * Light.Diffuse;
    Out.Diffuse += In.Diffuse * Material.Ambient * Light.Ambient;
    Out.Diffuse += Material.Emission;
    Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;
	Out.Tangent = float4(0.0, 0.0, 0.0, 0.0); //接ベクトルを出力
	Out.Binormal = float4(0.0, 0.0, 0.0, 0.0); //従法線を出力
	Out.TexCoord = In.TexCoord; //テクスチャ座標を出力
	matrix lightwvp;
	lightwvp = mul(World, Light.View);//ワールド行列＊ライトビュー行列
	lightwvp = mul(lightwvp, Light.Projection);//さらに＊ライトプロジェクション行列
	Out.ShadowPosition = mul(In.Position, lightwvp);//ライトカメラからみた頂点座標出力
}
