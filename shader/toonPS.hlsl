//
//#include "common.hlsl"
//
//Texture2D g_Texture : register(t0);
//SamplerState g_SamplerState : register(s0);
//Texture2D g_TextureToon : register(t1);
//
//void main(in PS_IN In, out float4 outDiffuse : SV_Target)
//{
//	//�@���𐳋K�����Ċi�[����
//	float4 normal = normalize(In.Normal);
//
//	float light = -dot(Light.Direction.xyz, normal.xyz);
//	light = saturate(light);
//	light = clamp(light, 0.035, 0.965);
//
//	////�v���O������ ���邳���Z���h�蕗�ɕϊ� if����light�̒l��3�i�K�ɒ���
//	//if (light > 0.6)
//	//	light = 1.0;
//	//else if (light > 0.4)
//	//	light = 0.8;
//	//else
//	//	light = 0.6;
//
//	float2 uv = light;
//	float3 toon;
//	uv.x += param.x; //C���ꂩ��󂯎�鐔�l���g���č��W�����炷
//
//	toon = g_TextureToon.Sample(g_SamplerState, uv); //���邳���擾
//
//
//	//�e�N�X�`������F���T���v�����O����
//    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
//
//	outDiffuse.rgb *= toon; //�e�N�X�`�������_�F�����邳
//
//    outDiffuse.a *= In.Diffuse.a;
//
//	//�G�b�W�̍쐬
//	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
//	eyev = normalize(eyev);
//	
//	//outDiffuse.rgb *= saturate(In.Diffuse.rgb * light); //�e�N�X�`�������_�F�����邳
//	
//	float d = dot(eyev, normal.xyz); //�@���Ǝ����x�N�g���̓���
//	if (d > -0.1) //d�̒l�𔻒�
//	{
//		outDiffuse.rgb *= 0.2; //�K����臒l�Ŗ��x�𗎂Ƃ�
//	}
//
//
//}
