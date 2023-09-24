
#include "common.hlsl"

static const float pi = 3.1415926535f;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	outDiffuse = float4(0.0f, 0.0f, 0.0f, 1.0f);
	//float2 uv = In.TexCoord - 0.5f;

	//float angle = atan2(uv.x, uv.y);
	//angle += pi;


	float nowHp = param.hp.x;
	float maxHp = param.hp.y;
	float oldHp = param.hp.z;

	//UV�l����s�N�Z���ւ̃X�P�[���ϊ����s��
	float gauge = In.TexCoord * maxHp;//�X�g���[�gVer
	//float gauge = frac(angle * 0.5 / pi) * param.hp.y;//�~�`Ver
	//HP�Q�[�W�̃O���[�������쐬����
	outDiffuse.rgb += param.lostColor.rgb * step(oldHp, gauge);
	//HP�Q�[�W�̗Ε������쐬����
	outDiffuse.rgb += param.baseColor.rgb * (1.0f - step(nowHp, gauge));
	//HP�Q�[�W�̐ԕ������쐬����
	outDiffuse.rgb += param.diffColor.rgb * (1.0f - step(oldHp, gauge)) * step(nowHp, gauge);
	
	//float dist = length(uv) / 0.5;
	//outDiffuse.a = (1.0 - step(1.0, dist)) * step(0.3, dist);
}
