
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureNormal : register(t1);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//ノーマルマップテクスチャから色をサンプリングする
	//このピクセルの法線マップのデータRGBA値を取得
	float4 normalMap = g_TextureNormal.Sample(g_SamplerState, In.TexCoord);
	//スケーリングして色→ベクトルデータへ変換する
	normalMap = normalMap * 2.0 - 1.0;

	float4 n = normalize(In.Normal);
	float4 t = normalize(In.Tangent);
	float4 b = normalize(In.Binormal);
	float4 normal;
	normal.xyz = t.xyz * normalMap.x + b.xyz * normalMap.y + n.xyz * normalMap.z;
	normal.w = 0.0;

	//法線を正規化して格納する
	normal = normalize(normal);

	//光源の向きと回転済みの法線とで内積を計算し、符号を反転して輝度を求める
	float light = -dot(Light.Direction.xyz, normal.xyz);
	//飽和演算(0.0～1.0の値にクランプする)
	light = saturate(light);


	//テクスチャがセットされていればサンプリングを行う
	if (Material.TextureEnable == false)
	{
		//テクスチャから色をサンプリングする
		outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);


		//透明度に頂点カラーの値を反映させる
		outDiffuse *= In.Diffuse;

		//透明度は輝度に影響しないのでそのまま使う
		//outDiffuse.a *= In.Diffuse.a;
	}
	//テクスチャがない場合は頂点カラーをそのまま使う
	else
	{
		outDiffuse = In.Diffuse;
	}

	//マテリアルの拡散光を反映させる
	outDiffuse *= Material.Diffuse;

	
	//テクスチャの色に輝度を乗算する
	outDiffuse.rgb *= light*1.5f;


	//マテリアルの環境光を反映させる
	outDiffuse.rgb = saturate(outDiffuse.rgb + Material.Ambient.rgb);

	//ブリンフォン鏡面反射
	//視線ベクトルを作成する（カメラからピクセルへ向かうベクトル）
	float3 evev = In.WorldPosition.xyz - CameraPosition.xyz;
	evev = normalize(evev);
	//ハーフベクトルを作成する（視線ベクトル＋ライトベクトル）
	float3 halfv = evev + Light.Direction.xyz;
	halfv = normalize(halfv);

	float specular = -dot(halfv, normal.xyz);
	saturate(specular);
	specular = pow(specular, Material.Shininess);
	//マテリアルのスペキュラカラーを反映させる
	outDiffuse.rgb = saturate(outDiffuse.rgb + (specular * Material.Specular.rgb));
}
