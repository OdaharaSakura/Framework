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
    for (int y = -9; y < 10; y++) //�㉺�́}12�s�N�Z���͈̔�
	{
		for (int x = -4; x < 5; x++) //���E�́}3�s�N�Z���͈̔�
		{//�����̒l��3�𒲐߂���ƌ��͈̔͂��ω�����
			float2 texCoord = In.TexCoord +
				float2(x * 4 / 1280.0, y * 9 / 720.0); //�e�N�X�`�����W�����炷
			float4 color = g_Texture.Sample(g_SamplerState, texCoord);
			//���x���v�Z
			float bright = color.r * 0.299 + color.g * 0.587 + color.b * 0.114;

			if (x != 0 || y != 0)
			{
				bloom -= color / (x * x + y * y);//�����ɂ���Č���
			}
		}
	}
	outDiffuse.rgb += bloom * 0.05f;//���ʂ����Z
}
