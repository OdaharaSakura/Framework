#include "common.hlsl"

Texture2D g_Texture : register(t0);//�ʏ�e�N�X�`��
Texture2D g_TextureDepthShadow : register(t1);//�V���h�E�}�b�v
SamplerState g_SamplerState : register(s0);
SamplerComparisonState  g_ShadowMapSampler : register(s1);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�����ł̐F�����ʂ̃e�N�X�`�������_�F���쐬���Ă���
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse *= In.Diffuse;
	In.ShadowPosition.xyz /= In.ShadowPosition.w; //���K���f�o�C�X���W�ɕϊ�
	In.ShadowPosition.x = In.ShadowPosition.x * 0.5f + 0.5f; //�e�N�X�`�����W�ɕϊ�
	In.ShadowPosition.y = (In.ShadowPosition.y * -0.5f) + 0.5f; //

	//�V���h�E�}�b�v�e�N�X�`�����A���C�g�J��������s�N�Z���܂ł̋����i�[�x�l�j���擾


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

		float3 shadowColor = outDiffuse.rgb * 0.5f;//�F���Â�����
		outDiffuse.rgb = lerp(outDiffuse.rgb, shadowColor, shadow);
	}
}
