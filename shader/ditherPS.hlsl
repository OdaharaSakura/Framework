//
//#include "common.hlsl"
//
//Texture2D g_Texture : register(t0);
//SamplerState g_SamplerState : register(s0);
//
//static const float g_DitherPattern[4][4] =
//{
//{ 0.0, 0.32, 0.08, 0.40 },
//{ 0.48, 0.16, 0.56, 0.24 },
//{ 0.12, 0.44, 0.04, 0.36 },
//{ 0.60, 0.28, 0.52, 0.20 }
//};
//
//void main(in PS_IN In, out float4 outDiffuse : SV_Target)
//{
//	//�@���𐳋K�����Ċi�[����
//	float4 normal = normalize(In.Normal);
//
//	//�����o�[�g
//    float light = -dot(Light.Direction.xyz, normal.xyz);
//    light = saturate(light);
//
//	//�e�N�X�`������F���T���v�����O����
//    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
//    outDiffuse.rgb *= light;
//    outDiffuse.a *= In.Diffuse.a;
//   
//	//�u�����t�H�����ʔ���
//    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
//    eyev = normalize(eyev);
//    float3 halfv = eyev + Light.Direction.xyz;
//    halfv = normalize(halfv);
//
//    float specular = -dot(halfv, normal.xyz);
//    saturate(specular);
//    specular = pow(specular, 30);
//    outDiffuse.rgb = saturate(outDiffuse.rgb + specular);
//
//    //�X�N���[�����W�֕ϊ�����
//    float2 pos = In.Tangent.xy / In.Tangent.w;
//    pos = pos * 0.5f + 0.5f;
//    float2 screen = float2(960.0, 540.0);
//    pos *= screen;
//    //�^�C���p�^�[���ɓ��Ă͂߂�
//    int x = (int)fmod(pos.x, 4.0f);
//    int y = (int)fmod(pos.y, 4.0f);
//    float dither = g_DitherPattern[y][x];
//    //�������l���Ⴂ�ꍇ�̓s�N�Z���o�͂��Ȃ�
//    if (dissolve.dissolveThreshold.x > dither)
//    {
//        discard;
//    }
//}
