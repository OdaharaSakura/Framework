#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState: register(s0);

//�u���[�� �P�x���������Č�������ɘR��錻��
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//���ʂɃe�N�X�`�����擾���ď����Ώۂ̃s�N�Z���̐F�Ə�Z���Ă���
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse *= In.Diffuse;//���_�F�ƍ������ďo��
	float4 bloom = 0.0; //�u���[�������̌��ʂ��i�[����ϐ�

	//��ʃT�C�Y X960 Y540�Ƃ����ꍇ
    for (int y = -3; y < 4; y++) //�㉺�́}12�s�N�Z���͈̔�
	{
		for (int x = -1; x < 2; x++) //���E�́}3�s�N�Z���͈̔�
		{//�����̒l��3�𒲐߂���ƌ��͈̔͂��ω�����
			float2 texCoord = In.TexCoord +
				float2(x * 0.03 / 960.0, y * 0.015 / 540.0); //�e�N�X�`�����W�����炷
			float4 color = g_Texture.Sample(g_SamplerState, texCoord);
			//���x���v�Z
			float bright = color.r * 0.299 + color.g * 0.587 + color.b * 0.114;
			//���x��臒l0.7���傫���A�������Ώۂ̃s�N�Z���łȂ�
			if (bright > 0.98 && (x != 0 || y != 0))
			{
				bloom += color / (x * x + y * y + 100.0f);//�����ɂ���Č����i�u���[���Ɋۂ݂��ł���j
			}
		}
	}
	outDiffuse.rgb += bloom * 0.5f;//���ʂ����Z
}
