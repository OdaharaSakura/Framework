
#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);
Texture2D g_TextureEnv : register(t1);
TextureCube g_TextureEnvCube : register(t2);//�L���[�u�}�b�v�󂯎��

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�@���𐳋K�����Ċi�[����
	float4 normal = normalize(In.Normal);

	//�����o�[�g
	float light = -dot(Light.Direction.xyz, normal.xyz);
	light = saturate(light);

	//�����x�N�g�������
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev);

	//���˃x�N�g�������
	float3 refv = reflect(eyev, normal.xyz);
	refv = normalize(refv);

	////���˃x�N�g��������}�b�s���O�p�̃e�N�X�`�����W���쐬����
	//float2 envTexCoord;
	//envTexCoord.x = -refv.x * 0.5 + 0.5;
	//envTexCoord.y = -refv.y * 0.5 + 0.5;

	////�e�N�X�`���o�C�A�X�w��t���ł̃e�N�X�`���̎擾
	//float4 EnvTexColor = g_TextureEnv.SampleBias(g_SamplerState, envTexCoord, 0.0f);
	// 

	float4 EnvTexColor = g_TextureEnvCube.Sample(g_SamplerState, refv);


	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);


	//�X�t�B�A�}�b�v����T���v�����O�����F�����Z��������
	outDiffuse.rgb = (EnvTexColor.rgb * 0.9) + (outDiffuse.rgb * 0.5); //�e�N�X�`�������_�F�����邳

    outDiffuse.a *= In.Diffuse.a;


}
