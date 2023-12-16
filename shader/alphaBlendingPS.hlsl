
#include "common.hlsl"


Texture2D g_Texture1 : register(t0); //�e�N�X�`��0��
Texture2D g_Texture2 : register(t1); //�e�N�X�`��1��
SamplerState	g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);	
	//outDiffuse *= In.Diffuse;

	////���N���b�v�i���l��0���ƕ`�悵�Ȃ��j
	//if (outDiffuse.a < 0.1f) discard;

	//�T���v�����O���ĐF���擾
	float4 tex1 = g_Texture1.Sample(g_SamplerState, In.TexCoord);

	//�T���v�����O���ĐF���擾
	float4 tex2 = g_Texture2.Sample(g_SamplerState, In.TexCoord);

	////���u�����f�B���O
	//outDiffuse.rgb = tex1.rgb * (1.0f - tex2.a) + tex2.rgb * tex2.a;
	//outDiffuse.a = In.Diffuse.a;

	// �����̃e�N�X�`���̃A���t�@�l���擾
	float alpha1 = tex1.a;
	float alpha2 = tex2.a;

	// �d�Ȃ��������̃A���t�@�l���v�Z
	float blendedAlpha = alpha1 + alpha2 * (1.0 - alpha1);

	// �A���t�@�u�����f�B���O
	outDiffuse.rgb = tex1.rgb * (1.0 - alpha2) + tex2.rgb * alpha2;
	outDiffuse.a = blendedAlpha;

	// �����A���t�@�l�����ȉ��Ȃ�`�悵�Ȃ��i���������j
	if (outDiffuse.a < 0.1f)
		discard;


	//outDiffuse.rgb = tex1.rgb;	//�΂̃e�N�X�`����
	//outDiffuse.a = tex1.a;		//�c���[�̌`��

	//outDiffuse *= In.Diffuse; //�f�t���[�Y(���_�̖��邳)������

		//�O���[�X�P�[���ϊ�
	//float gray;
	//gray = 0.299 * outDiffuse.r + 0.587 * outDiffuse.g + 0.114 * outDiffuse.b;
	//outDiffuse.r = gray;
	//outDiffuse.g = gray;
	//outDiffuse.b = gray;

	//�Z�s�A�ϊ�
	//float4 sepia = float4(0.960, 0.784, 0.580, 1.0);
	//outDiffuse *= sepia;

}
